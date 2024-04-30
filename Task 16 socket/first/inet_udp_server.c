#include <stdio.h>
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
    struct hostent *host;
    char buf[15];
    socklen_t size = sizeof(struct sockaddr_in);

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));
 
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(2003); 

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    int tmp = bind(fd, (struct sockaddr *) &server, size);
    if(tmp == -1){
        printf("ERR BIND %d", errno);
        close(fd);
        //unlink("/tmp/stream_serv");
        return -1;
    } 
    
    size = sizeof(client);

    tmp = recvfrom(fd, buf, 10, 0, (struct sockaddr *) &client, &size);
    if(tmp == -1){
        printf("ERR recv %d", errno);
        close(fd); 
        //unlink("/tmp/stream_serv");
        return -1;
    }

    printf("%s\n", buf);
    buf[0] = '\000';
    strcat(buf, "Hello");
    
    tmp = sendto(fd, buf, 10, 0, (struct sockaddr *) &client, size); 
    if(tmp == -1){
        printf("ERR send %d", errno);
        close(fd); 
        //unlink("/tmp/stream_serv");
        return -1;
    }

    buf[0] = '\000';  
    close(fd);
    //unlink("/tmp/stream_serv");
    return 0;
}