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
#if SOCKET
void data_process(int sockefd)
{

}
#else
void data_process(int fd1,int fd2, int fileflag)
{
	int pid;

	if(fileflag == 0) {
		pid = fork();
		if(pid < 0)
		  err_sys("write fork error");
		else if(pid == 0){
			data_write(fd1);
			exit(0);
		}
		else {
			if((pid = fork()) < 0) {
				err_sys("read fork error");
			}
			else if(pid == 0) {
				data_read(fd2);
				exit(0);
			}
			else {
				full_flag = 0;
			}
		}
	}
	else if(fileflag == 1) {
		//				printf("world\n");
		if((pid = fork()) < 0)
		  err_sys("write fork error");
		else if(pid == 0){
			data_write(fd2);
			exit(0);
		}
		else {
			if((pid = fork()) < 0) {
				err_sys("read fork error");
			}
			else if(pid == 0) {
				data_read(fd1);
				exit(0);
			}
			else {
				full_flag = 0;
			}
		}			
	}
}
#endif
