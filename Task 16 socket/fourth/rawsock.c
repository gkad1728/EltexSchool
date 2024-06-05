#include "lib.h"

struct massage{
    short src_port;
    short des_port;
    short length;
    short check_sum;
    char payload[BUF_SIZE];
};

struct ip_header{
    char Ver_IHL;
    char DS;
    short length;
    short identification;
    short flags_offset;
    char TTL; 
    char Transport_Proto;
    short Checksum;
    int src_ip;
    int dest_ip;
    struct massage msg;
};

int main(){
    int fd;  
    //struct massage msg;
    struct ip_header ip_msg;
    char buf[BUF_SIZE];
    struct sockaddr_in server, client;
    socklen_t size = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP); 

    int flag = 1;
    int tmp = setsockopt(fd, SOL_RAW, IP_HDRINCL, (void *)&flag, (socklen_t) sizeof(flag));
    
    ip_msg.Ver_IHL = 84; // 84 = 0101 0100 в младших битах 4 в старших 5
    ip_msg.DS = 0;
    ip_msg.length = htons(28 + BUF_SIZE);
    ip_msg.identification = 0;
    ip_msg.flags_offset = 0; //000
    ip_msg.TTL = 50;
    ip_msg.Transport_Proto = 17;
    ip_msg.Checksum = 0;
    ip_msg.src_ip = INADDR_ANY;
    ip_msg.dest_ip = INADDR_ANY;
    //ip_msg.msg = &msg;

    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(MAIN_PORT); 

    ip_msg.msg.src_port = htons(PORT);
    ip_msg.msg.des_port = htons(MAIN_PORT);
    ip_msg.msg.length = htons(BUF_SIZE);
    ip_msg.msg.check_sum = 0;
    strcat(ip_msg.msg.payload, "Hi");

    if(sendto(fd, &ip_msg, sizeof(ip_msg), 0, (struct sockaddr *) &server, size) == -1){
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