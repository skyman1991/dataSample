#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fd = open("data.txt",O_RDWR);
	int i;
	unsigned short int buf[100];
	read(fd,buf,20);
	for(i = 0; i < 20; ++i) {
		printf("%d\t",buf[i]);
	}
	printf("\n");
	return 0;
}
