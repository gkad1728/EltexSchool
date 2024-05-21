#include "lib.h"

int main(){
    int fd;
    struct sockaddr_in server;
    char buf[BUF_SIZE];  
    socklen_t size = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_STREAM, 0); 

    memset(&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(MAIN_PORT);

    if(connect(fd, (const struct sockaddr *) &server, size) == -1){
        printf("ERR CONNECT %d", errno);
        close(fd); 
        return -1;
    }
    else{
        close(fd);
    }

    fd = socket(AF_INET, SOCK_STREAM, 0); 
    server.sin_port = htons(MAIN_PORT+2);
    if(connect(fd, (const struct sockaddr *) &server, size) == -1){
        printf("ERR CONNECT %d", errno);
        close(fd); 
        return -1;
    }

    if(send(fd, "Connect tcp", BUF_SIZE, 0) == -1){
        printf("ERR send %d", errno); 
        close(fd); 
        return -1;
    }

    while(buf[0] != 'q' || buf[1] != '\000'){
        buf[0] = '\000'; 
        if(recv(fd, buf, BUF_SIZE, 0) == -1){
            printf("ERR recv %d", errno); 
            close(fd); 
            return -1;
        } 
        printf("%s\n", buf);
        printf("Введите сообщение серверу (до %d символов, q - отключение): ", BUF_SIZE);
        buf[0] = '\000';
        fgets(buf, BUF_SIZE, stdin);
        for(int i = 0; i < BUF_SIZE; i++){
            if(buf[i] == '\n'){
                buf[i] = '\000';
                break;
            } 
        }
        if(send(fd, buf, BUF_SIZE, 0) == -1){
            printf("ERR send %d", errno); 
            close(fd); 
            return -1;
        }
    } 
    
    close(fd); 

    return 0;
}