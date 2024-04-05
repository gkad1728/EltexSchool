#include <stdio.h>
#include <string.h>
#include <fcntl.h>          
#include <sys/stat.h>        
#include <mqueue.h>
#include <unistd.h> 

int main(){
    mqd_t mqdes1, mqdes2;
    struct mq_attr attr;
    attr.mq_maxmsg = 5;
    attr.mq_msgsize = 50;
    attr.mq_curmsgs = 1;
    unsigned int prio;

    char msg[] = {"Hello"};
    char input_buf[40];
    
    mqdes1 = mq_open("/queue5", O_WRONLY | O_CREAT, 0666, &attr);
    mqdes2 = mq_open("/queue6", O_RDONLY | O_CREAT, 0666, &attr);
    if(mqdes1 == -1){
        printf("ERR open\n");
        return 1;
    }
    if(mqdes2 == -1){
        printf("ERR open\n");
        return 1;
    }

    if(mq_send(mqdes1, msg, strlen(msg), 1) == -1){
        printf("ERR send\n");
        return 1;
    }
    printf("S -> C : %s\n", msg);

   //sleep(3);

    if(mq_receive(mqdes2, input_buf, 50, &prio) == -1){
        printf("ERR read\n");
        return 1;
    }
    printf("S <- C : %s\n", input_buf);

    if(mq_close(mqdes1) == -1){
        printf("ERR close\n");
        return 1;
    }

    if(mq_unlink("/queue5") == -1){
        printf("ERR unlink\n");
        return 1;
    }
    if(mq_close(mqdes2) == -1){
        printf("ERR close\n");
        return 1;
    }

    if(mq_unlink("/queue6") == -1){
        printf("ERR unlink\n");
        return 1;
    }

    return 0;

    
}