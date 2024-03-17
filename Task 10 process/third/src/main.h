#ifndef __MAIN_H__
#define __MAIN_H__

 
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h> 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <limits.h>  
#include <string.h> 
#include <sys/wait.h>
#include <time.h>

void resizewin();
void sig_winch(int signo);
void DV_init();
int win_del();
int DV_end();
int path_get(char** path);
int Dir_del(int n, struct dirent **namelist);
int dir_enter(char** path, char *name);
int use_file(char* path, char* name);
#endif 