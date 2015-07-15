#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd;
	char p[30] = "hello world";
	fd = open("data.txt",O_RDWR|O_CREAT,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	write(fd,p,11);
	close(fd);
	return 0;
}
