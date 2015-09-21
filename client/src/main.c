#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../include/ad7606.h"
#include "../include/data.h"
#include "../include/sock.h"

int main()
{
	int pid;
	int fd1,fd2;
	int sockfd;
	int i = 0;
	//char s[12] = "hello world";

#if SOCKET
	sockfd = socket_init();
	//send(sockfd,s,12,0);
	printf("done\n");
#else
	if((fd1 = open("../data/data1.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0){
		err_sys("open file1 error");
		exit(-1);
	}
	if((fd2 = open("../data/data2.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)) < 0){
		err_sys("open file2 error");
		exit(-1);
	}
#endif

	pi_Init(5000);
	pi_InitAD7606();	
	pi_InitSignal();
	ad7606_StartRecord(1000);

	while(1)
	{		
#if SOCKET
		if(full_flag == 1) {
			data_process(sockfd);
		}
#else
		if(full_flag == 1) {
			data_process(fd1,fd2,file_flag);
		}
#endif
	}
	return 0;
}
