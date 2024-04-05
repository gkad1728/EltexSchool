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
    strcat(massage.massage, "Hi");

    key_Queue = ftok("Server", QUEUE_ID); 
    msqid = msgget(key_Queue, 0);
    if(msqid == -1){
        printf("ERR msgget\n");
        return 1;
    }

    input_massage_size = msgrcv(msqid, &input_buf, 50, 0, 0);
    if(input_massage_size == -1){
        printf("ERR msgrcv\n");
        return 1;
    }
    printf("C <- S : %s\n", input_buf.massage);

    if(msgsnd(msqid, &massage, strlen(massage.massage), 0) == -1){
        printf("ERR msgsnd\n");
        return 1;
    }
    printf("C -> S : %s\n", massage.massage);

    //msgctl(msqid, IPC_RMID, 0);

    return 0;
}