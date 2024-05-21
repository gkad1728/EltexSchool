#include "lib.h"

int fds_passive[MAX_AMOUNT_CLIENTS + 1], fds_active[MAX_AMOUNT_CLIENTS + 1];
short array_empty[MAX_AMOUNT_CLIENTS];
pthread_t thread[MAX_AMOUNT_CLIENTS + 1];
struct sockaddr_in server[MAX_AMOUNT_CLIENTS + 1];

void *client_thread(void *args){
    int *tmp = (int *) args;
    int number = *tmp;
    char buf[BUF_SIZE];
    buf[0] = '\000';
    socklen_t size = sizeof(struct sockaddr_in);
    struct sockaddr_in client;

    while(1){
        fds_active[number] = accept(fds_passive[number], (struct sockaddr *) &client, &size);
        array_empty[number - 1] = 1; 
        while(buf[0] != 'q' || buf[1] != '\000'){
            buf[0] = '\000';
            strcat(buf, "TIME");
            if(send(fds_active[number], buf, sizeof(buf), 0) == -1){
                printf("ERR SEND fds№%d %d\n", number, errno);
                buf[0] = 'q';
                buf[1] = '\000';
            }
            else{
                buf[0] = '\000'; 
                if(recv(fds_active[number], buf, BUF_SIZE, 0) == -1){
                    printf("ERR RECV fds№%d %d\n", number, errno);
                    buf[0] = 'q';
                    buf[1] = '\000';
                }
                printf("client %d: %s\n", number, buf);
            }
        }
        send(fds_active[number], buf, sizeof(buf), 0);
        array_empty[number - 1] = 0;
        close(fds_active[number]);
        buf[0] = '\000';
    }
}

void *connection_thread(void *args){
    struct sockaddr_in client;
    int number, tmp;
    int buf[BUF_SIZE];
    socklen_t size = sizeof(struct sockaddr_in);

    server[0].sin_family = AF_INET;
    server[0].sin_addr.s_addr = INADDR_ANY;
    server[0].sin_port = htons(MAIN_PORT); 

    fds_passive[0] = socket(AF_INET, SOCK_STREAM, 0);
    if(bind(fds_passive[0], (struct sockaddr *) &server[0], size)){
        printf("ERR BIND %d\n", errno);
        close(fds_passive[0]);
    }
    else{
        listen(fds_passive[0], 1);
        for(int i = 1; i <= MAX_AMOUNT_CLIENTS; i++){
            array_empty[i-1] = 0;
            fds_passive[i] = socket(AF_INET, SOCK_STREAM, 0);
            server[i].sin_family = AF_INET;
            server[i].sin_addr.s_addr = INADDR_ANY;
            server[i].sin_port = htons(MAIN_PORT + i); 
            if(bind(fds_passive[i], (struct sockaddr *) &server[i], size)){
                printf("ERR BIND %d\n", errno);
                close(fds_passive[i]);
                array_empty[i-1] = -1;
            }
            else{
                listen(fds_passive[i], 1);
                number = i;
                pthread_create(&thread[i], NULL, client_thread, (void *) &number);
            }
        }
        while(1){
            for(int i = 0; i < MAX_AMOUNT_CLIENTS; i++){
                if(array_empty[i] == 0){
                    number = i + 1;
                    array_empty[i] = 2;
                    break;
                }
            }
            fds_active[0] = accept(fds_passive[0], (struct sockaddr *) &client, &size);
            buf[0] = number + 48;
            buf[1] = '\000';
            printf("Подключение к порту %d номера %d\n", htons(MAIN_PORT + number), number);
            if(send(fds_active[0], buf, sizeof(buf), 0) == -1){
                printf("ERR SEND fds№%d %d\n", 0, errno);
            }
            if(recv(fds_active[0], buf, BUF_SIZE, 0) == -1){
                    printf("ERR RECV fds№%d %d\n", 0, errno); 
            }
            close(fds_active[0]);
        }
    }
}

int main(){
    pthread_create(&thread[0], NULL, connection_thread, NULL);

    printf("q - принудительный выход b - запрет на подключение и ожидание выхода\n");
    
    char ifexit = 0;
    while(ifexit != 'q'){
        scanf("%c", &ifexit);
    }

    close(fds_active[0]);
    close(fds_passive[0]);
    pthread_cancel(thread[0]);

    for(int i = 1; i <= MAX_AMOUNT_CLIENTS; i++){
        if(array_empty[i] == 1)
            close(fds_active[i]);
        close(fds_passive[i]);
        pthread_cancel(thread[i]);
    }

    return 0;
}
/*
Создаем потоки с ацептами.
слушающий принимает подключение и возвращает порт свободного
клиент его принимает и подключается к свободному
*/