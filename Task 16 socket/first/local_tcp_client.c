#include <stdio.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h> 
#include <errno.h> 

int main(){
    int fd;
    struct sockaddr_un server;
    char buf[100];  

    fd = socket(AF_LOCAL, SOCK_STREAM, 0);  

    memset(&server, 0, sizeof(server));

    server.sun_family = AF_LOCAL; 
    strcat(server.sun_path, "/tmp/stream_serv");
    
    socklen_t size = sizeof(struct sockaddr_un);

    int tmp = connect(fd, (const struct sockaddr *) &server, size);
    if(tmp == -1){
        printf("ERR %d", errno);
    }

    strcat(buf, "Hi");
    tmp = send(fd, buf, 10, 0);
    if(tmp == -1){
        printf("ERR send %d", errno); 
        close(fd); 
        return -1;
    } 
    buf[0] = '\000';
    tmp = recv(fd, buf, 10, 0);
    if(tmp == -1){
        printf("ERR recv %d", errno); 
        close(fd); 
        return -1;
    } 
    printf("%s\n", buf);
    close(fd); 
    return 0;
}