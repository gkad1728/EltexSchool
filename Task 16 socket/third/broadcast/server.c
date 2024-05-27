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
    struct sockaddr_in server, client; 
    socklen_t size = sizeof(struct sockaddr_in);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_BROADCAST;
    client.sin_port = htons(7777); 

    //int tmp = inet_addr("255.255.255.255");

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    int flag = 1;
    int tmp = setsockopt(fd, SOL_SOCKET, SO_BROADCAST, (void *)&flag, (socklen_t) sizeof(flag));

    if(sendto(fd, "Hello", 5, 0, (struct sockaddr *) &client, size) == -1){
        printf("ERR send %d\n", errno);
    }

    close(fd);
    return 0;
}