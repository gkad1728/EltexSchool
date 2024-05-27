#include <stdio.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h> 
#include <errno.h> 
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netdb.h>
#include <stdlib.h> 

int main(){
    int fd;
    struct sockaddr_in client;
    struct ip_mreqn mreqn;
    char buf[15];
    socklen_t size = sizeof(struct sockaddr_in);

    mreqn.imr_ifindex = 0;
    mreqn.imr_multiaddr.s_addr = inet_addr("224.0.0.1");
    mreqn.imr_address.s_addr = INADDR_ANY;

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(7777); 

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    
    if(bind(fd, (struct sockaddr *) &client, size) == -1){
        printf("ERR bind %d\n", errno);
        close(fd);
        return 1;
    }

    int tmp = setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreqn, sizeof(mreqn));

    if(recvfrom(fd, buf, 5, 0, (struct sockaddr *) NULL, NULL) == -1){
        printf("ERR recv %d\n", errno);
    }
    else{
        printf("%s\n", buf);
    }

    close(fd);
    return 0;
}