#ifndef __LIB_H__
#define __LIB_H__

#include <stdio.h>
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

#define MAX_AMOUNT_CLIENTS 15 //Максимальное кол-во клиентов без учета потока подключения
#define MAX_TEST_CLIENTS 10 //Число клиентов для теста.
#define MAIN_PORT 7777
#define BUF_SIZE 50

#endif 
