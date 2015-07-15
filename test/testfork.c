#include "apue.h"

int main()
{
	int n = 0;
	int pid;

	while(1) 
	{
		if(n == 2) {
			if((pid = fork()) < 0)
				err_sys("fork error");
			else if(pid == 0){
				int ppid = getpid();
				printf("%d: hello world\n",ppid);
				exit(0);
			}
			else {
				n = 0;
			}
		}
		else {
			sleep(1);
			printf("what's up\n");
			++n;
		}
	}
	return 0;
}
