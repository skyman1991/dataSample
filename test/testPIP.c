#include "apue.h"

int main()
{
	pid_t pid;
	pid = fork();
	
	if(pid == 0){
		printf("this is child\n");
		exit(0);
	}
	else{ 
		sleep(1);
		printf("this is parent\n");
		exit(0);
	}
}
