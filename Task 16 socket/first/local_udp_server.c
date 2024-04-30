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
    char buf[15];
    socklen_t size = sizeof(struct sockaddr_un);

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    strcat(server.sun_path, "/tmp/stream_serv");
    server.sun_family = AF_LOCAL;  

    fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
    int tmp = bind(fd, (struct sockaddr *) &server, size);
    if(tmp == -1){
        printf("ERR BIND %d", errno);
        close(fd);
        unlink("/tmp/stream_serv");
        return -1;
    } 
    
    size = sizeof(client);

    tmp = recvfrom(fd, buf, 10, 0, (struct sockaddr *) &client, &size);
    if(tmp == -1){
        printf("ERR recv %d", errno);
        close(fd); 
        unlink("/tmp/stream_serv");
        return -1;
    }

    printf("%s\n", buf);
    buf[0] = '\000';
    strcat(buf, "Hello");
    
    tmp = sendto(fd, buf, 10, 0, (struct sockaddr *) &client, size); 
    if(tmp == -1){
        printf("ERR send %d", errno);
        close(fd); 
        unlink("/tmp/stream_serv");
        return -1;
    }

    buf[0] = '\000';  
    close(fd);
    unlink("/tmp/stream_serv");
    return 0;
}