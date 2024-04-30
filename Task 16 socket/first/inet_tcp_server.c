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
    int fd_passive, fd_active;
    struct sockaddr_in server, client;
    char buf[15];
    socklen_t size = sizeof(struct sockaddr_in);

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client)); 

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2002); 

    fd_passive = socket(AF_INET, SOCK_STREAM, 0);
    int tmp = bind(fd_passive, (struct sockaddr *) &server, size);
    if(tmp == -1){
        printf("ERR BIND %d", errno);
        close(fd_passive);
        //unlink("/tmp/stream_serv");
        return -1;
    }
    listen(fd_passive, 2);

    fd_active = accept(fd_passive, (struct sockaddr *) &client, &size);
 
    tmp = recv(fd_active, buf, 10, MSG_WAITALL);
    if(tmp == -1){
        printf("ERR recv %d", errno);
        close(fd_passive);
        close(fd_active);
        //unlink("/tmp/stream_serv");
        return -1;
    }

    printf("%s\n", buf);
    buf[0] = '\000';
    strcat(buf, "Hello");
    
    tmp = send(fd_active, buf, 10, 0); 
    if(tmp == -1){
        printf("ERR send %d", errno);
        close(fd_passive);
        close(fd_active);
        //unlink("/tmp/stream_serv");
        return -1;
    }

    buf[0] = '\000'; 
    close(fd_active);
    close(fd_passive); 
    return 0;
}