#ifndef __LIB_H__
#define __LIB_H__

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void *func_shopper(void *args);
void *func_loader(void *args);

#endif
