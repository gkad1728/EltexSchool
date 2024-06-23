#include "lib.h"

struct udp_header{
    short src_port;
    short des_port;
    short length;
    short check_sum;
    char payload[BUF_SIZE-8];
};

int main(){
    int fd;  
    struct udp_header msg1, *msg2; 
    char buf[BUF_SIZE+20];
    struct sockaddr_in server;
    socklen_t size = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP); 

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(MAIN_PORT);

    msg1.src_port = htons(PORT);
    msg1.des_port = htons(MAIN_PORT);
    msg1.length = htons(BUF_SIZE);
    msg1.check_sum = 0;
    strcat(msg1.payload, "Hi"); 
 
    if(sendto(fd, &msg1, BUF_SIZE, 0, (struct sockaddr *) &server, size) == -1){
        printf("ERR send %d\n", errno);
        close(fd);
        return -1;
    }

    while(1){
        if(recvfrom(fd, buf, BUF_SIZE+20, 0, (struct sockaddr *) &server, &size) == -1){
            printf("RECV %s\n", buf); 
        }
        else{
            msg2 = &buf[20];
        }
        printf("Что-то поймал"); 
        if(msg2->des_port == msg1.src_port){
            printf(", server - %s\n", msg2->payload); 
            break;
        }
        else{
            printf(", но это не то, что нужно\n");
        }
    }

    close(fd);
    return 0;
}