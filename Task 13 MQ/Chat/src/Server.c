#include "Server.h"
#define QUEUE_RD_SERVER "/queuerds11"
#define QUEUE_WR_SERVER "/queuewrs11"
char chat_buf[100]; 
char user_buf[50];
int counter_user = 1, counter_chat = 1;
mqd_t mqdes_rds, mqdes_wrs;
int tmp; 

int main(){
    struct mq_attr attr;
    attr.mq_maxmsg = 5;
    attr.mq_msgsize = 150; 
    unsigned int prio; 
    pthread_t thread;
    int status;

    mqdes_rds = mq_open(QUEUE_RD_SERVER, O_RDWR | O_CREAT, 0666, &attr);
    mqdes_wrs = mq_open(QUEUE_WR_SERVER, O_RDWR | O_CREAT, 0666, &attr);
    if(mqdes_rds == -1 || mqdes_wrs == -1){
        printf("ERR open\n");
        return 1;
    }

    init_graf(); 
 
    pthread_create(&thread, NULL, thread_chat, NULL);
    if(mq_send(mqdes_wrs, "1 Test", 100, 10) == -1){
        printf("F");
    } 
    if(mq_send(mqdes_rds, "1 Start chat", 100, 10) == -1){
        printf("F");
    } 
    while(tmp != 113){
        tmp = getch();
        if(tmp == 99){  
            refreshwin(); 
            //mq_send(mqdes_rds, "7", 100, 10);
        }   
    } 
    refreshwin(); 
    mq_send(mqdes_rds, "2 exit server", 100, 10);  
    pthread_join(thread, (void *)&status);
    sleep(1);




    end_graf();
    if(mq_close(mqdes_rds) == -1 || mq_close(mqdes_wrs) == -1){
        printf("ERR close\n");
        return 1;
    }
    if(mq_unlink(QUEUE_RD_SERVER) == -1 || mq_unlink(QUEUE_WR_SERVER) == -1){
        printf("ERR unlink\n");
        return 1;
    }
    return 0;
}