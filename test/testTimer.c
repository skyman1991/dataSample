#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>

static int count = 0;
static int n = 0;
int data[100];

void set_timer(int value)
{
	struct itimerval t;
	t.it_value.tv_sec = value;
	t.it_value.tv_usec = 0;
	t.it_interval.tv_sec = value;
	t.it_interval.tv_usec = 0;
	setitimer(ITIMER_REAL,&t,NULL);
}
void timer_process(int m)
{
	data[count] = count++;
//	printf("%d ",count++);
}

void INT_process(int sig)
{
	int i;
	for(i = 0; i < 20; i++)
		printf("%d  ",data[i]);
	printf("\n");
}
int main()
{
	int i;

	signal(SIGINT,INT_process);
	signal(SIGALRM,timer_process);
	set_timer(1);

	while(1) {
//		printf("now n = %d ",n++);
//		sleep(1);
//		if(count == 20) {
//			for(i = 0; i < count; i++) {
//				printf("%d ",data[i]);
//				for(i = 0; i < 12345; i++);
//			}
//			printf("\n");
//			break;
//		}
		if(count == 10)
			set_timer(0);
	}
	for(i = 0; i <20; i++)
		printf("%d  ",data[i]);
	printf("\n");
}
