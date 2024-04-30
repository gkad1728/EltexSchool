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
    struct sockaddr_in server;
    char buf[100];  

    fd = socket(AF_INET, SOCK_STREAM, 0);  

    memset(&server, 0, sizeof(server));

    //int portno = atoi("ni");
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;//*(struct in_addr *) host->h_addr_list[0];
    //bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    server.sin_port = htons(2002); 
    
    socklen_t size = sizeof(struct sockaddr_in);

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