#include "lib.h"

struct massage{
    short src_port;
    short des_port;
    short length;
    short check_sum;
    char payload[BUF_SIZE];
};

int main(){
    int fd;  
    struct massage msg;
    char buf[BUF_SIZE];
    struct sockaddr_in server, client;
    socklen_t size = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP); 
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(MAIN_PORT); 

    msg.src_port = htons(PORT);
    msg.des_port = htons(MAIN_PORT);
    msg.length = htons(BUF_SIZE);
    msg.check_sum = 0;
    strcat(msg.payload, "Hi");

    if(sendto(fd, &msg, sizeof(msg), 0, (struct sockaddr *) &server, size) == -1){
        printf("ERR send %d\n", errno);
        close(fd);
        return -1;
    }

    while(1){
        if(recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *) &server, &size) == -1){
            printf("RECV %s\n", buf); 
        }
        printf("Что-то поймал");
        if(server.sin_port == htons(MAIN_PORT)){
            printf("- %s\n", buf);
            break;
        }
        else{
            printf(", но это не то, что нужно\n");
        }
    }

    close(fd);
    return 0;
}