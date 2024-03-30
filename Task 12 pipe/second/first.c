#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    char *name_fifofile = "file.fifo";
    int writefd;

    mkfifo(name_fifofile, 0666);

    writefd = open(name_fifofile, O_WRONLY);
    write(writefd, "Hello", 5);
    close(writefd);
    return 0;
}