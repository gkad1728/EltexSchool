#include "lib.h"

int main(){
    int fd;
    struct sockaddr_in server, client; 
    char buf[BUF_SIZE];
    socklen_t size = sizeof(struct sockaddr_in);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(MAIN_PORT); 

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(bind(fd, (struct sockaddr *) &server, size) == -1){
        printf("ERR bind %d\n", errno);
        close(fd);
        return -1;
    }

    if(recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *) &client, &size) == -1){
        printf("ERR recv %d\n", errno);
        close(fd);
        return -1;
    }

    printf("%s\n", buf);
    buf[0] = '\000';
    strcat(buf, "Hello");

    if(sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *) &client, size) == -1){
        printf("ERR send %d\n", errno);
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}