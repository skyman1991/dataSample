#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "ad7606.h"
#include "data.h"
 
FIFO_T g_tAD;
struct itimerval itimer;
int full_flag; // FIFO full flag

/*********************************************
 * name: pi_Init
 * function: Init pi
 * paramerer: _speed: SPI speed, kHz
 * return: no return value
 * ******************************************/
void pi_Init(u32 _spispeed)  // danwei kHz
{
	int i;
	u32 speed  = _spispeed * 1000;

	if(wiringPiSetup() == -1){
		printf("Pi Error: GPIO Init failed\n");
		exit(-1);
	}

	if(wiringPiSPISetup(CHAN,speed) == -1) {
		printf("Pi Error: SPI Init failed\n");
		exit(-1);
	}

	for(i = 0; i < 6; i++) {
		pinMode(i,OUTPUT);
	}
}

/**********************************************
 * name: pi_InitAD7606
 * function: Init AD7606
 * parameter: void
 * return: no return value
 * *******************************************/
void pi_InitAD7606(void)

{
	ad7606_SetOS(0); //set over sample: no over sample
	AD_RANGE_10V;
	ad7606_Reset(); 
	AD_CONVST_HIGH;  //set convst to high
}

/*********************************************
 * name: timer_config
 * function: Init timer,set time value
 * parameter: void
 * return: no return value
 * ******************************************/
void pi_SetTimer(u32 _ulFreq)
{
	u32 freq_s = 1/_ulFreq;
	u32 freq_us = (1000000/(float)_ulFreq) - freq_s*1000000;
//	signal(SIGALRM,timer_process);  // register the signal
	itimer.it_value.tv_sec = freq_s;
	itimer.it_value.tv_usec = freq_us;
	itimer.it_interval.tv_sec = freq_s;
	itimer.it_interval.tv_usec = freq_us;
	setitimer(ITIMER_REAL,&itimer,0);
}

/********************************************
 * name: timer_process
 * function: called when timer timeout
 * parameter: signo: signal to deliver
 * return: no return value
 * ******************************************/
void timer_process(int signo)
{
	ad7606_IRQSrc();
}

/*********************************************
 * name: signal_init
 * function: initialize signal
 * parameter: void
 * return: no return value
 * *******************************************/
void pi_InitSignal()
{
	signal(SIGALRM,timer_process);
}

/*********************************************
 * name: ad7606_Reset
 * function: ad7606 hardware reset
 * parameter: void
 * return: no return value
 * ******************************************/
void ad7606_Reset(void)
{
	int i;

	//HIGH to reset, 50ns at least
	AD_RESET_LOW;  
	AD_RESET_HIGH;
	for(i = 0; i < 20; i++) {   //maybe not enough, if so, increase the number
		AD_RESET_HIGH;
	}
	AD_RESET_HIGH;
	AD_RESET_LOW;
}

/********************************************
 * name: ad7606_SetOS
 * function: set oversampling
 * parameter: _ucMode,oversampling mode(0:no sampling)
 * return: no return value
 * *****************************************/
void ad7606_SetOS(u8 _ucMode)
{
	if(_ucMode == 1) {
		AD_OS2_0;
		AD_OS1_0;
		AD_OS0_1;
	} 
	else if(_ucMode == 2) {
		AD_OS2_0;
		AD_OS1_1;
		AD_OS0_0;
	} 
	else if(_ucMode == 3) {
		AD_OS2_0;
		AD_OS1_1;
		AD_OS0_1;
	} 
	else if(_ucMode == 4) {
		AD_OS2_1;
		AD_OS1_0;
		AD_OS0_0;
	} 
	else if(_ucMode == 5) {
		AD_OS2_1;
		AD_OS1_0;
		AD_OS0_1;
	} 
	else if(_ucMode == 6) {
		AD_OS2_1;
		AD_OS1_1;
		AD_OS0_0;
	} 
	else {
		AD_OS2_0;
		AD_OS1_0;
		AD_OS0_0;
	}
}

/**********************************************
 * name: ad7606_StartConv
 * function: start convst of ad7606
 * parameter: void
 * return: no return value
 * ********************************************/
void ad7606_StartConv(void)
{
	int i;

	//Rising edge to start,low level must be at least 25ns
	AD_CONVST_LOW;
	for(i = 0; i < 10; i++) {  //maybe not enough or to much
		AD_CONVST_LOW;
	}
	AD_CONVST_HIGH;
}

/***********************************************
 * name:ad7606_ReadBytes
 * fuction: read the sample result of ad7606
 * parameter: void
 * return: u16 data of one time sampling
 * *********************************************/
u16 ad7606_ReadBytes()
{
	u16 usData;
	u8 *data = (u8*)&usData;
	
	wiringPiSPIDataRW(0,data,2);

	return usData;

}

/************************************************
 * name: ad7606_IRQSrc
 * function: read the value of ad7606
 * parameter: void
 * return: no return value
 * **********************************************/
void ad7606_IRQSrc()
{
	u8 i;
	u16 usReadValue;
//printf("watch it\n");
	//TIM_ClearFlag()
	
//	AD_CS_LOW();
	for(i = 0; i < CH_NUM; i++) {
		usReadValue = ad7606_ReadBytes();
		if(g_tAD.usWrite < FIFO_SIZE) {
			g_tAD.usBuf[g_tAD.usWrite] = usReadValue;
			++g_tAD.usWrite;
		} else {
//		printf("hehe\n");
		  full_flag = 1;
		  file_flag = (file_flag + 1) % 2;
		  g_tAD.usWrite = 0;
		}
	}
//	AD_CS_HIGH;

	ad7606_StartConv();
}

/******************************************************
 * name: getAdcFromFifo
 * function: read adc value from fifo
 * paramerter: _usReadAdc: pointer that pointed to adc result
 * return: 1: ok  0: now have no data
 * ****************************************************/
u8 getAdcFromFifo(u16 *_usReadAdc)
{
	u16 usWrite;

	// DISABLE_INT()
	usWrite = g_tAD.usWrite;
	// ENABLE_INT();
	
	if(usWrite != g_tAD.usRead) {
		*_usReadAdc = g_tAD.usBuf[g_tAD.usRead];

		//DISABLE_INT()
		if(++g_tAD.usRead >= FIFO_SIZE)
			g_tAD.usRead = 0;
		//ENABLE_INT()

		return 1;
	}
	return 0;
}

/******************************************************
 * name: ad7606_StartRecord
 * function: start sample
 * parameter: _ulFreq: sampling frequency, Hz
 * return: no return value
 * ***************************************************/
void ad7606_StartRecord(u32 _ulFreq)
{
	ad7606_StartConv();
	g_tAD.usRead = 0;
	g_tAD.usRead = 0;
	
	pi_SetTimer(_ulFreq);
}

/*****************************************************
 * name: ad7606_StopRecord
 * function: stop sampling
 * paramerer: void
 * retrun: no return value
 * **************************************************/
void ad7606_StopRecord(void)
{
	pi_SetTimer(0);
}

