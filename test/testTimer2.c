#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <errno.h>

static int count = 0;
static int n = 0;
double data[100];

int flag = 0;

void timer_process(int m) {
	data[count++] = (double) times(NULL) / (double) sysconf(_SC_CLK_TCK);
	flag = 1;
//	write(2, "hehe\n", 5); 你好
}

int main(void) {
	struct itimerval t;
	int i;

	signal(SIGALRM,timer_process); 

	siginterrupt(SIGALRM, 1);

	t.it_value.tv_sec = 1;
	t.it_value.tv_usec = 0;
	t.it_interval.tv_sec = 1;
	t.it_interval.tv_usec = 0;

	setitimer(ITIMER_REAL,&t,NULL);

	int fd[2];
	
	pipe(fd);

	char buf[1];

	int ret;

	while(1) {

		long i;
		for (i = 0; i < 1000000000; ++i) {
			if(flag) {break;}
		}

		//ret = read(0, buf, 1);

		printf("ret = %d, errno = %d\n", ret, errno);
	
		printf("%lf\n",data[count-1]);
		fflush(stdout);

		flag = 0;

	}
}
