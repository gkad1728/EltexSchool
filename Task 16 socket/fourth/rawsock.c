#include "lib.h"

struct massage{
    short src_port;
    short des_port;
    short length;
    short check_sum;
    char payload[BUF_SIZE-28];
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
    struct massage msg1, *msg2;
    struct ip_header ip_msg, *ip_msg2;
    char buf[BUF_SIZE];
    struct sockaddr_in server, client;
    socklen_t size = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP); 

    int flag = 1;
    int tmp = setsockopt(fd, SOL_RAW, IP_HDRINCL, (void *)&flag, (socklen_t) sizeof(flag));
    
    ip_msg.Ver_IHL = 69; // 69 = 0100 0101 в младших битах 4 в старших 5
    ip_msg.DS = 0;
    ip_msg.length = htons(28 + BUF_SIZE);
    ip_msg.identification = 0;
    ip_msg.flags_offset = 0; //000
    ip_msg.TTL = 50;
    ip_msg.Transport_Proto = 17;
    ip_msg.Checksum = 0;
    ip_msg.src_ip = INADDR_ANY;
    ip_msg.dest_ip = INADDR_ANY;
    

    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(MAIN_PORT); 

    ip_msg.msg.src_port = htons(PORT);
    ip_msg.msg.des_port = htons(MAIN_PORT);
    ip_msg.msg.length = htons(BUF_SIZE);
    ip_msg.msg.check_sum = 0;

    msg1.src_port = htons(PORT);
    msg1.des_port = htons(MAIN_PORT);
    msg1.length = htons(BUF_SIZE);
    msg1.check_sum = 0;

    strcat(ip_msg.msg.payload, "Hi");
    strcat(msg1.payload, "Hi");

    if(sendto(fd, &ip_msg, BUF_SIZE, 0, (struct sockaddr *) &server, size) == -1){
        printf("ERR send %d\n", errno);
        close(fd);
        return -1;
    }

    while(1){
        if(recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *) &server, &size) == -1){
            printf("RECV %s\n", buf); 
        }
        else{
            msg2 = &buf[20];
            ip_msg2 = buf;
        }
        printf("Что-то поймал");
        if(msg2->des_port == msg1.src_port){
            printf(", server - %s\n", msg2->payload);

            /*printf("\n------------\n");
            printf("намальный / мой\nVer_IHL %d %d\n", ip_msg2->Ver_IHL, ip_msg.Ver_IHL);
            printf("DS %d %d\n", ip_msg2->DS, ip_msg.DS);
            printf("length %d %d\n", ip_msg2->length, ip_msg.length);
            printf("ident %d %d\n", ip_msg2->identification, ip_msg.identification);
            printf("flags %d %d\n", ip_msg2->flags_offset, ip_msg.flags_offset);
            printf("TTL %d %d\n", ip_msg2->TTL, ip_msg.TTL);
            printf("Transport %d %d\n", ip_msg2->Transport_Proto, ip_msg.Transport_Proto);
            printf("Checksum %d %d\n", ip_msg2->Checksum, ip_msg.Checksum);
            printf("src ip %d %d\n", ip_msg2->src_ip, ip_msg.src_ip);
            printf("dest ip %d %d\n", ip_msg2->dest_ip, ip_msg.dest_ip); 
            printf("ip --- %d\n", INADDR_ANY);
            printf("\n------------\n");*/
            break;
        }
        else{
            printf(", но это не то, что нужно\n");
        }
    }

    close(fd);
    return 0;
}