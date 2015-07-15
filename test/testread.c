#include "apue.h"
#include <fcntl.h>

int main()
{
	int fd = open("data.txt",O_RDWR);
	char s[6];
	read(fd,s,5);
	printf("%s",s);
	read(fd,s,6);
	printf("%s\n",s);
	close(fd);
	return 0;
}
