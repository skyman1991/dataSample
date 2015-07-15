#ifndef _AD7606_H
#define _AD7606_H

#define u32 unsigned int
#define u16 unsigned short int
#define u8  unsigned char

#define CH_NUM             1         // the number of smple channel
#define FIFO_SIZE          2*512*2  // the size of fifo
#define CHAN               0         // pi's SPI channel	

//define the crotrl GPIO of ad7606
#define AD_RESET_PIN       0 
#define AD_CONVST_PIN      1
#define AD_RANGE_PIN       2
#define AD_OS0_PIN         3
#define AD_OS1_PIN         4
#define AD_OS2_PIN	       5
//songme useful option
//#define AD_CS_LOW          digitalWrite(AD_CS_PIN,0)
//#define AD_CS_HIGH         digitalWrite(AD_CS_PIN,1)

#define AD_RESET_LOW       digitalWrite(AD_RESET_PIN,0)
#define AD_RESET_HIGH      digitalWrite(AD_RESET_PIN,1)

#define AD_CONVST_LOW      digitalWrite(AD_CONVST_PIN,0)
#define AD_CONVST_HIGH     digitalWrite(AD_CONVST_PIN,1)

#define AD_RANGE_5V        digitalWrite(AD_RANGE_PIN,0)
#define AD_RANGE_10V       digitalWrite(AD_RANGE_PIN,1)

#define AD_OS0_0           digitalWrite(AD_OS0_PIN,0)
#define AD_OS0_1           digitalWrite(AD_OS0_PIN,1)

#define AD_OS1_0           digitalWrite(AD_OS1_PIN,0)
#define AD_OS1_1           digitalWrite(AD_OS1_PIN,1)

#define AD_OS2_0		   digitalWrite(AD_OS2_PIN,0)
#define AD_OS2_1		   digitalWrite(AD_OS2_PIN,1)

// ad data buffer
typedef struct
{
	u16 usRead;
	u16 usWrite;
	u16 usCount;
	u16 usBuf[FIFO_SIZE];
}FIFO_T;

extern int full_flag; // FIFO full flag

//function to call from outside 
extern void ad7606_Reset(void);
extern void ad7606_SetOS(u8 _ucMode);
extern void ad7606_StartRecord(u32 _ulFreq);
extern void ad7606_StopRecord(void);
extern void ad7606_IRQSrc();

extern void pi_SetTimer(u32 _ulFreq);  //
extern void pi_InitAD7606(void);
extern void pi_Init(u32 _spispeed);
extern void pi_InitSignal();
extern u8 getDataFromFifo(u16 *_usReadAdc);

extern FIFO_T g_tAD;


#endif
