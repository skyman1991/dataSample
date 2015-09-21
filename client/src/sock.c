#include "../include/sock.h"

#define MAXSLEEP   128         //socket retry sleep time
#define SERVER     "192.168.191.1" 
#define PORT       8888        //socket port

int 
connect_retry(int sockfd,const struct sockaddr *addr,socklen_t alen) 
{
	int numsec;
	for (numsec = 1; numsec <= MAXSLEEP; numsec <<= 1) {
		if(connect(sockfd,addr,alen) == 0)
			return 0;
		if(numsec <= MAXSLEEP/2)
			sleep(numsec);
		printf("sleep\n");
	}
	return -1;
}


/*********************************************
 * name: socket_init
 * function: Init socket and try to connet to server
 * paramerer: *pserverip: server ip
 *			  port: socket port
 * return: 0: sucess  -1: error
 * ******************************************/
int socket_init()
{
	int sockfd;
	struct sockaddr_in s_add;
	unsigned short portnum = PORT;
	char *server_ip = SERVER;

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1) {
		err_sys("socket failed!");
		return -1;
	}

	memset(&s_add,0,sizeof(struct sockaddr_in));
	s_add.sin_family = AF_INET;
	s_add.sin_addr.s_addr = inet_addr(server_ip);
	s_add.sin_port = htons(portnum);

	if((connect_retry(sockfd,(struct sockaddr *)(&s_add),sizeof(struct sockaddr))) == -1) {
		err_sys("connect failed!");
		return -1;
	}
	return sockfd;
}

