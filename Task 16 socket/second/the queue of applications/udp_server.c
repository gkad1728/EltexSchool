#include "lib.h"
#define NAME_SEM "/semid"
#define NAME_SEM1 "/semid1"
#define NAME_QE "/queue10"

char ifexit = 0;
pthread_t thread[MAX_AMOUNT_CLIENTS + 1]; 
int fds[MAX_AMOUNT_CLIENTS + 1];
struct sockaddr_in server[MAX_AMOUNT_CLIENTS + 1], client[MAX_AMOUNT_CLIENTS + 1];
socklen_t size = sizeof(struct sockaddr_in);
mqd_t mqdes;
sem_t *semid, *semid1;
struct mq_attr attr;

void *client_thread(void *args){
    char buf[BUF_SIZE];
    unsigned int prio;
    int *tmp = (void *) args;
    int number = *tmp;
    sem_post(semid1);
    printf("start server %d\n", number);
    while(ifexit != 'q'){
        sem_wait(semid);
        printf("wait number %d\n", number);
        buf[0] = '\000';
        if(mq_receive(mqdes, (char *)&client[number].sin_port, sizeof(client[0].sin_port), &prio) == -1){
            printf("ERR read %d\n", errno); 
        }
        else{ 
            while(buf[0] != 'q' || buf[1] != '\000'){
                buf[0] = '\000';
                strcat(buf, "TIME");
                if(sendto(fds[number], buf, sizeof(buf), 0, (struct sockaddr *) &client[number], size) == -1){
                    printf("ERR SEND fds№%d %d\n", number, errno);
                    buf[0] = 'q';
                    buf[1] = '\000';
                }
                else{
                    if(buf[0] != 'q' && buf[1] != '\000'){
                        buf[0] = '\000'; 
                        if(recvfrom(fds[number], buf, sizeof(buf), 0, (struct sockaddr *) &client[number], &size) == -1){
                            printf("ERR RECV fds№%d %d\n", number, errno);
                            buf[0] = 'q';
                            buf[1] = '\000';
                        }
                        printf("client %d %d: %s\n", number, client[number].sin_port, buf);
                    }
                }
            }
        }
    }
}

void *connection_thread(void *args){ 
    int number;

    attr.mq_maxmsg = MAX_AMOUNT_CLIENTS;
    attr.mq_msgsize = sizeof(client[0].sin_port);
    //attr.mq_curmsgs = 1;

    mqdes = mq_open(NAME_QE, O_RDWR | O_CREAT, 0666, &attr);
    if(mqdes == -1){
        printf("ERR open queue\n");
    }

    for(int i = 1; i <= MAX_AMOUNT_CLIENTS; i++){
        number = i;
        pthread_create(&thread[i], NULL, client_thread, (void *)&number);
        sem_wait(semid1);
    }

    char buf[BUF_SIZE];
    while(ifexit != 'q'){
        if(recvfrom(fds[0], buf, BUF_SIZE, 0, (struct sockaddr *) &client[0], &size) == -1){
            printf("ERR recv %d", errno);
        }
        else{
            printf("CONNECT %d\n", client[0].sin_port);
            sem_post(semid);
            if(mq_send(mqdes, (char *) &client[0].sin_port, sizeof(client[0].sin_port), 1) == -1){
                printf("ERR send\n"); 
            } 
        }
    }
}

int main(){
    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    semid = sem_open(NAME_SEM, O_CREAT, 0666, 0); 
    semid1 = sem_open(NAME_SEM1, O_CREAT, 0666, 0); 

    for(int i = 0; i <= MAX_AMOUNT_CLIENTS; i++){    
        server[i].sin_family = AF_INET;                 
        server[i].sin_addr.s_addr = INADDR_ANY;        
        server[i].sin_port = htons(MAIN_PORT + i);

        client[i].sin_family = AF_INET;                 
        client[i].sin_addr.s_addr = INADDR_ANY;

        fds[i] = socket(AF_INET, SOCK_DGRAM, 0);

        if(bind(fds[i], (struct sockaddr *) &server[i], size) == -1){
            printf("ERR BIND %d № %d", errno, i);
            close(fds[i]); 
            ifexit = 'q';
        }
    }

    pthread_create(&thread[0], NULL, connection_thread, NULL);

    printf("q - принудительный выход\n");
    while(ifexit != 'q'){
        scanf("%c", &ifexit); 
    }

    for(int i = 0; i <= MAX_AMOUNT_CLIENTS; i++){
        if(thread[i] != 0)
            pthread_cancel(thread[i]);
        close(fds[i]);
    }

    if(sem_close(semid) == -1){
        printf("ERR ftran");
        return -1;
    }
    if(sem_unlink(NAME_SEM) == -1){
        printf("ERR ftran");
        return -1;
    }
    if(sem_close(semid1) == -1){
        printf("ERR ftran");
        return -1;
    }
    if(sem_unlink(NAME_SEM1) == -1){
        printf("ERR ftran");
        return -1;
    }

    if(mq_close(mqdes) == -1){
        printf("ERR close\n");
        return 1;
    }

    if(mq_unlink(NAME_QE) == -1){
        printf("ERR unlink\n");
        return 1;
    }

    return 0;
}