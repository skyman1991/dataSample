#include "../include/ad7606.h"
#include "../include/data.h"
#include "apue.h"

int enter_flag = 0;

int file_flag = 1; //which file to write

/*
void data_process()
{
	u16 data;
	for(g_tAD.usRead = 0,g_tAD.usWrite = FIFO_SIZE; g_tAD.usRead < FIFO_SIZE; g_tAD.usRead++)
		if(getAdcFromFifo(&data) == 1)
			printf("%d\t",data);
		else {
			err_sys("print data error");
		}
}
*/

void data_write(int _fd)
{
	lseek(_fd,0,SEEK_SET);
	u16 data;
	for(g_tAD.usRead = 0,g_tAD.usWrite = FIFO_SIZE; g_tAD.usRead < FIFO_SIZE; g_tAD.usRead++)
		if(getAdcFromFifo(&data) == 1)
			write(_fd,&data,2);
		else {
			err_sys("print data error");
		}
}

void data_read(int _fd)
{
	u16 data;
	lseek(_fd,0,SEEK_SET);
	while(1) {
		enter_flag++;
		if(read(_fd,&data,2) > 0 ) {
			if(enter_flag == 8) {
				printf("%d\n",data);
				enter_flag = 0;
			}
			else
				printf("%d\t",data);
		}
		else{
			enter_flag = 0;
			break;
		}
	}
}

