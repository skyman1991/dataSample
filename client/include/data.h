#ifndef _DATA_H
#define _DATA_H

#include "sock.h"

extern int file_flag; //whitch file to write
extern void data_write(int _fd);
extern void data_read(int _fd);
#if SOCKET
extern void data_process(int sockfd);
#else
extern void data_process(int fd1,int fd2, int fileflag);
#endif

#endif
