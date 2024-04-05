#ifndef __LIB_H__
#define __LIB_H__

#include <stdio.h>
#include <string.h>
#include <fcntl.h>          
#include <sys/stat.h>        
#include <mqueue.h>
#include <unistd.h> 
#include <pthread.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <curses.h> 
#include <dirent.h>
#include <limits.h>  
#include <sys/wait.h>

/* коды сообщений
    1 - Старт
    2 - Конец
    3 - Подключение
    4 - Отключение
    5 - сообщение
    6 - пусто
*/

void *thread_chat(void *args);
void init_graf();
void refreshwin(); 
void end_graf();
void win_del();

#endif 