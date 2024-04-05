#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define QUEUE_ID 5

struct msgbuf{
    long mtype;
    char massage[30];
};

int main(){ 
    key_t key_Queue;
    int msqid;
    ssize_t input_massage_size;
    struct msgbuf massage;
    struct msgbuf input_buf;
    massage.mtype = 10;
    strcat(massage.massage, "Hello"); 

    key_Queue = ftok("Server", QUEUE_ID);
    msqid = msgget(key_Queue, (IPC_CREAT | 0644));
    if(msqid <= 0){
        printf("ERR msgget\n");
        return 1;
    }

    if(msgsnd(msqid, &massage, strlen(massage.massage), 0) == -1){
        printf("ERR msgsnd\n");
        return 1;
    }
    printf("S -> C : %s\n", massage.massage);

    input_massage_size = msgrcv(msqid, &input_buf, 30, 0, 0);
    if(input_massage_size == -1){
        printf("ERR msgrcv\n");
        return 1;
    }
    printf("S <- C : %s\n", input_buf.massage);

    msgctl(msqid, IPC_RMID, 0);
    
    return 0;
}