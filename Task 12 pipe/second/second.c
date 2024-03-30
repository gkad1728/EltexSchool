#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/stat.h>
#include <fcntl.h>

int main(){
    char *name_fifofile = "file.fifo", buf;
    int readfd;

    readfd = open(name_fifofile, O_RDONLY);
    while(read(readfd, &buf, 1)) 
        write(STDOUT_FILENO, &buf, 1);
    write(STDOUT_FILENO, "\n", 1);
    close(readfd);
    return 0;
}