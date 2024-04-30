#include <stdio.h>
#include <stdlib.h>
#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h> 
#include <errno.h> 
#include <netinet/in.h>
#include <netdb.h>

int main(){
    int fd;
    struct sockaddr_in server, client;
    char buf[15];
    struct hostent *host;
    socklen_t size = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_DGRAM, 0);   

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));
 
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2003); 

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(2004); 

    int tmp = bind(fd, (struct sockaddr *) &client, size);
    if(tmp == -1){
        printf("ERR BIND %d", errno);
        close(fd); 
        //unlink("/tmp/stream_client");
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
        //unlink("/tmp/stream_client");
        return -1;
    } 
    buf[0] = '\000';
    tmp = recv(fd, buf, 10, 0);
    if(tmp == -1){
        printf("ERR recv %d", errno); 
        close(fd); 
        //unlink("/tmp/stream_client");
        return -1;
    } 
    printf("%s\n", buf);
    close(fd); 
    //unlink("/tmp/stream_client");
    return 0;
}