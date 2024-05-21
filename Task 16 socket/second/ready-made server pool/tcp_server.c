#include "lib.h"

char ifexit = 0;
int free_array[MAX_AMOUNT_CLIENTS + 1];
int fds_passive[MAX_AMOUNT_CLIENTS + 1];
int fds_active[MAX_AMOUNT_CLIENTS + 1];
pthread_t thread[MAX_AMOUNT_CLIENTS + 1];

void *client_thread(void *args){
    int *tmp = args;
    int number = *tmp;
    char buf[BUF_SIZE];
    socklen_t size = sizeof(struct sockaddr_in);

    while(ifexit != 'q'){
        fds_active[number] = accept(fds_passive[number], NULL, &size);
        printf("Connect %d\n", number);
        free_array[number] = 1;
        buf[0] = '\000';
        while(buf[0] != 'q' || buf[1] != '\000'){
            buf[0] = '\000';
            strcat(buf, "TIME");
            if(send(fds_active[number], buf, sizeof(buf), 0) == -1){
                printf("ERR send %d %d\n", number, errno);
                break;
            }
            else{
                buf[0] = '\000';
                if(recv(fds_active[number], buf, BUF_SIZE, 0) == -1){
                    printf("ERR recv %d %d\n", number, errno);
                    break;
                }
                else{
                    printf("Client %d: %s\n", number, buf);
                }
            }
        }
        send(fds_active[number], "Disconnect", sizeof("Disconnect"), 0);
        printf("Disconnect %d\n", number);
        close(fds_active[number]);
        free_array[number] = 0;
    }
}

void *connection_thread(void *args){
    struct sockaddr_in server;
    int number;
    int buf[BUF_SIZE];
    socklen_t size = sizeof(struct sockaddr_in);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    for(int i = 0; i <= MAX_AMOUNT_CLIENTS; i++){
        fds_passive[i] = socket(AF_INET, SOCK_STREAM, 0);
        server.sin_port = htons(MAIN_PORT + i);
        if(bind(fds_passive[i], (struct sockaddr *) &server, size) == -1){
            printf("ERR BIND %d %d", i, errno); 
            free_array[i] = -1;
        }
        else{
            listen(fds_passive[i], 1);
            number = i;
            free_array[i] = 0;
            if(i > 0)
                pthread_create(&thread[i], NULL, client_thread, (void *)&number);
            printf("Запущен сервер %d с портом %d\n", i, htons(MAIN_PORT + i));
        } 
    }
    free_array[0] = 1;

    while(ifexit != 'q'){
        for(int i = 1; i <= MAX_AMOUNT_CLIENTS; i++){
            if(free_array[i] == 0){
                server.sin_port = htons(MAIN_PORT+i);
                fds_active[0] = accept(fds_passive[0], NULL, &size);
                printf("Попытка подключения к порту %d\n", server.sin_port);
                free_array[i] = 3;
                if(send(fds_active[0], &server.sin_port, sizeof(server.sin_port), 0) == -1){
                    printf("ERR send connect %d\n", errno);
                }
                close(fds_active[0]);
                break;
            }
        } 
    }
}

int main(){
    pthread_create(&thread[0], NULL, connection_thread, NULL);

    printf("q - принудительный выход b - запрет на подключение и ожидание выхода\n");
    
    while(ifexit != 'q'){
        scanf("%c", &ifexit);
    }

    for(int i = 0; i <= MAX_AMOUNT_CLIENTS; i++){ 
        if(fds_active[i]) 
            close(fds_active[i]);
        close(fds_passive[i]);
        pthread_cancel(thread[i]); 
    }

    return 0;
}