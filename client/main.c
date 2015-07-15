#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "ad7606.h"
#include "data.h"

int main()
{
	int pid;
	int fd1,fd2;
	int i = 0;
	if((fd1 = open("data1.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0){
		err_sys("open file1 error");
		exit(-1);
	}
	if((fd2 = open("data2.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0){
		err_sys("open file2 error");
		exit(-1);
	}
	pi_Init(5000);
	pi_InitAD7606();	
	pi_InitSignal();
	ad7606_StartRecord(1000);
// printf("hello world\n");	
	while(1)
	{		
		//printf("nihao\n");
		if(full_flag == 1) {
	//	printf("nihao\n");
			if(file_flag == 0) {
				pid = fork();
	//			printf("hello\n");
				if(pid < 0)
					err_sys("write fork error");
				else if(pid == 0){
					printf("write 1\n");
					data_write(fd1);
					exit(0);
				}
				else {
					if((pid = fork()) < 0) {
						err_sys("read fork error");
					}
					else if(pid == 0) {
						printf("read 1\n");
						data_read(fd2);
						exit(0);
					}
					else {
						full_flag = 0;
					}
				}
			}
			else if(file_flag == 1) {
//				printf("world\n");
				if((pid = fork()) < 0)
					err_sys("write fork error");
				else if(pid == 0){
					printf("write 2\n");
					data_write(fd2);
					exit(0);
				}
				else {
					if((pid = fork()) < 0) {
						err_sys("read fork error");
					}
					else if(pid == 0) {
						printf("read 2\n");
						data_read(fd1);
						exit(0);
					}
					else {
						full_flag = 0;
					}
				}			
			}
		}
	}

//	close(fd1);
//	close(fd2);
return 0;
}
