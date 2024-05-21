#include "lib.h"

char ifexit = 0;
pthread_t thread[MAX_AMOUNT_CLIENTS + 1];
int fds[MAX_AMOUNT_CLIENTS + 1];  
int amount_clients = 0;

void *client_thread(void *args){
    int *number = (int *) args;
    char buf[BUF_SIZE];
    buf[0] = '\000';
    while(buf[0] != 'q' || buf[1] != '\000'){
        buf[0] = '\000';
        strcat(buf, "TIME");
        if(send(fds[*number], buf, sizeof(buf), 0) == -1){
            printf("ERR SEND fds№%d %d\n", *number, errno);
            buf[0] = 'q';
            buf[1] = '\000';
        }
        else{
            if(buf[0] != 'q' && buf[1] != '\000'){
                buf[0] = '\000'; 
                if(recv(fds[*number], buf, BUF_SIZE, 0) == -1){
                    printf("ERR RECV fds№%d %d\n", *number, errno);
                    buf[0] = 'q';
                    buf[1] = '\000';
                }
                printf("client %d: %s\n", *number, buf);
            }
        }
    }
    send(fds[*number], buf, sizeof(buf), 0);
    close(fds[*number]);
    amount_clients--;
    fds[*number] = -1;
}

void *connection_thread(void *args){
    struct sockaddr_in server, client[MAX_AMOUNT_CLIENTS]; 
    int number, tmp;
    socklen_t size = sizeof(struct sockaddr_in);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(MAIN_PORT); 

    fds[0] = socket(AF_INET, SOCK_STREAM, 0);
    if(bind(fds[0], (struct sockaddr *) &server, size)){
        printf("ERR BIND %d\n", errno);
        close(fds[0]);
    }
    else{
        listen(fds[0], MAX_AMOUNT_CLIENTS);
        while(1){
            number = -1;
            for(int i = 1; i <= MAX_AMOUNT_CLIENTS; i++){
                if(fds[i] == -1){
                    number = i;
                    break;
                }
            }
            if(number > 0){
                fds[number] = accept(fds[0], (struct sockaddr *) &client[number], &size);
                tmp = number;
                pthread_create(&thread[number + 1], NULL, client_thread, (void *)&tmp);
                amount_clients++;
            }
            else{
                sleep(1);
            }
        }
    }
}

void *disconnection_thread(void *args){
    int status;
    for(int i = 1; i <= MAX_AMOUNT_CLIENTS; i++){
        if(fds[i] != -1){
            pthread_join(thread[i], (void **)&status);
            close(fds[i]);
        }
    }
}

int main(){
    int status;

    for(int i = 0; i < MAX_AMOUNT_CLIENTS; i++)
        fds[i] = -1;
    
    pthread_create(&thread[0], NULL, connection_thread, NULL);

    printf("q - принудительный выход b - запрет на подключение и ожидание выхода\n");
    while(ifexit != 'q'){
        scanf("%c", &ifexit);
        if(ifexit == 'b'){
            pthread_cancel(thread[0]);
            pthread_create(&thread[0], NULL, disconnection_thread, NULL); 
            pthread_join(thread[0], (void **)&status);
            ifexit = 'q';
        }
    }
    close(fds[0]);
    return 0;

}