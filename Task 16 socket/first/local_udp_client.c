#include <stdio.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h> 
#include <errno.h> 

int main(){
    int fd;
    struct sockaddr_un server, client;
    char buf[100];  

    fd = socket(AF_LOCAL, SOCK_DGRAM, 0);   

    memset(&server, 0, sizeof(server));

    server.sun_family = AF_LOCAL; 
    strcat(server.sun_path, "/tmp/stream_serv");
    client.sun_family = AF_LOCAL; 
    strcat(client.sun_path, "/tmp/stream_client");
    
    socklen_t size = sizeof(struct sockaddr_un);

    int tmp = bind(fd, (struct sockaddr *) &client, size);
    if(tmp == -1){
        printf("ERR BIND %d", errno);
        close(fd); 
        unlink("/tmp/stream_client");
        return -1;
    } 

    tmp = connect(fd, (const struct sockaddr *) &server, size);
    if(tmp == -1){
        printf("ERR %d", errno);
    }

    strcat(buf, "Hi");
    tmp = send(fd, buf, 10, 0);
    if(tmp == -1){
        printf("ERR send %d", errno); 
        close(fd); 
        unlink("/tmp/stream_client");
        return -1;
    } 
    buf[0] = '\000';
    tmp = recv(fd, buf, 10, 0);
    if(tmp == -1){
        printf("ERR recv %d", errno); 
        close(fd); 
        unlink("/tmp/stream_client");
        return -1;
    } 
    printf("%s\n", buf);
    close(fd); 
    unlink("/tmp/stream_client");
    return 0;
}