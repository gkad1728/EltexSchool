
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
#include <time.h>

int main(){
    while(1){
    printf("%d", getch());
    }
    return 0;
}