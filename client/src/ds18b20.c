#include "apue.h"
#include "../include/ds18b20.h"
#include <fcntl.h>

#define TEMPBUF 128

float read_temp()
{
	float temp;
	int i,j;
	int fd;
	int ret;
	char buf[TEMPBUF];
	char tempbuf[5];

	fd = open("/sys/bus/w1/devices/28-00000495db35/w1_slave",O_RDONLY);
	if(fd == -1) {
		err_sys("oepn device file error");
		exit(-1);
	}
	
	ret = read(fd,buf,TEMPBUF);
	if(ret == 0) { 
		err_sys("read nothing");
		exit(-1);
	}
	else if(ret == -1) {
		err_sys("read temperature error");
		close(fd);
		exit(-1);
	}

	for(i = 0; i < sizeof(buf); ++i) {
		if(buf[i] == 't') {
			for(j = 0; j < sizeof(tempbuf); ++j) 
			  tempbuf[j] = buf[i+j+2];
		}
	}
	temp = (float)atoi(tempbuf)/1000;
	close(fd);
	
	return temp;
}
