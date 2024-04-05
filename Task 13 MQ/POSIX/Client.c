#include <stdio.h>
#include <string.h>
#include <fcntl.h>          
#include <sys/stat.h>        
#include <mqueue.h>

int main(){
    mqd_t mqdes1, mqdes2;
    char msg[] = {"Hi"};
    char input_buf[40];
    unsigned int prio;

    mqdes1 = mq_open("/queue5", O_RDONLY);
    mqdes2 = mq_open("/queue6", O_WRONLY);

    if(mqdes1 == -1){
        printf("ERR open\n");
        return 1;
    }
    if(mqdes2 == -1){
        printf("ERR open\n");
        return 1;
    }

    if(mq_receive(mqdes1, input_buf, 50, &prio) == -1){
        printf("ERR read\n");
        return 1;
    }
    printf("C <- S : %s\n", input_buf);

    if(mq_send(mqdes2, msg, strlen(msg), 1) == -1){
        printf("ERR send\n");
        return 1;
    }
    printf("C -> S : %s\n", msg);

    if(mq_close(mqdes1) == -1){
        printf("ERR close\n");
        return 1;
    }
    if(mq_close(mqdes2) == -1){
        printf("ERR close\n");
        return 1;
    }
    
    return 0;
}