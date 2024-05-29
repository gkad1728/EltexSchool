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

int main(){
    int fd; 
    char buf[15]; 

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP); 
    
#if(0)    
    if(recvfrom(fd, buf, 15, 0, (struct sockaddr *) NULL, NULL) == -1){
        printf("ERR recv\n");
    }
    else{
        printf("RECV %s\n", buf);
    }
#endif

#if(1)
    while(1){
        if(recvfrom(fd, buf, 15, 0, (struct sockaddr *) NULL, NULL) != -1){
            printf("RECV %s\n", buf);
            break;
        }
    }
#endif
    close(fd);
    return 0;
}