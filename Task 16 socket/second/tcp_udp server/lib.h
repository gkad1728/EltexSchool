#ifndef __LIB_H__
#define __LIB_H__

#include <stdio.h>
#include <mqueue.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h> 
#include <errno.h> 
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>        
#include <sys/select.h> 
#include <sys/stat.h>   

#define MAX_AMOUNT_CLIENTS 3 //Максимальное кол-во клиентов без учета потока подключения
#define MAIN_PORT 7777
#define BUF_SIZE 50

#endif 
