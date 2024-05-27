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
    client.sin_addr.s_addr = inet_addr("224.0.0.1");
    client.sin_port = htons(7777); 

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sendto(fd, "Hello", 5, 0, (struct sockaddr *) &client, size) == -1){
        printf("ERR send %d\n", errno);
    }

    close(fd);
    return 0;
}