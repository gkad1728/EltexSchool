#include "lib.h"

int main(){
    int fd;
    struct sockaddr_in server, client;
    char buf[BUF_SIZE]; 
    socklen_t size = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_DGRAM, 0);   

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(MAIN_PORT+1);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY; 

    if(bind(fd, (struct sockaddr *) &client, size) == -1){
        printf("ERR BIND %d", errno);
        close(fd);  
        return -1;
    }

    if(sendto(fd, "Connect", sizeof("Connect"), 0, (struct sockaddr *) &server, size) == -1){
        printf("ERR SEND fds№ %d\n", errno);
        close(fd);  
        return -1;
    }

    server.sin_port = htons(MAIN_PORT+3);

    if(sendto(fd, "Connect", sizeof("Connect"), 0, (struct sockaddr *) &server, size) == -1){
        printf("ERR SEND fds№ %d\n", errno);
        close(fd);  
        return -1;
    }

    buf[0] = '\000';
    if(recvfrom(fd, buf, sizeof(server.sin_port), 0, (struct sockaddr *) &server, &size) == -1){
        printf("ERR RECV fds№%d \n", errno);
        close(fd);  
        return -1; 
    }

    while(buf[0] != 'q' || buf[1] != '\000'){
        buf[0] = '\000';
        printf("Введите сообщение серверу (до %d символов, q - отключение): ", BUF_SIZE);
        fgets(buf, BUF_SIZE, stdin);
        for(int i = 0; i < BUF_SIZE; i++){
            if(buf[i] == '\n'){
                buf[i] = '\000';
                break;
            }
        }
        if(sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *) &server, size) == -1){
            printf("ERR SEND fds№%d\n", errno);
            close(fd);  
            return -1;
        }
        else{
            if(buf[0] != 'q' || buf[1] != '\000'){
                buf[0] = '\000';
                if(recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *) &server, &size) == -1){
                    printf("ERR RECV fds№%d \n", errno);
                    close(fd);  
                    return -1; 
                }
                printf("server: %s\n", buf);
            }
        }
    }

    close(fd);
    return 0;
}