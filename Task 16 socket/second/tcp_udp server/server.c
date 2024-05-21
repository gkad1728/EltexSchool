#include "lib.h"

char ifexit = 0;
pthread_t thread[MAX_AMOUNT_CLIENTS + 1]; 
int fd_tcp, fd_udp, fd_udp_active;          //Слушающие сервера
int fds_tcp[MAX_AMOUNT_CLIENTS + 1];        //Массив, где первый пассивый, сервер а остальные активные
socklen_t size = sizeof(struct sockaddr_in);

void *client_thread_tcp(void *args){
    int *tmp = args;
    int number = *tmp;
    struct sockaddr_in client;
    char buf[BUF_SIZE];
    printf("запуск процесса %d\n", number);

    buf[0] = '\000';
    fds_tcp[number] = accept(fds_tcp[0], (struct sockaddr *) &client, &size);
    while(buf[0] != 'q' || buf[1] != '\000'){
        if(recv(fds_tcp[number], buf, BUF_SIZE, 0) == -1){
            printf("ERR RECV TCP fds№%d %d\n", number, errno);
            buf[0] = 'q';
            buf[1] = '\000';
            break;
        }
        else{
            printf("client: %s\n", buf);
            if(buf[0] != 'q' || buf[1] != '\000'){
                buf[0] = '\000';
                strcat(buf, "TIME");
                if(send(fds_tcp[number], buf, BUF_SIZE, 0) == -1){
                    printf("ERR SEND TCP fds№%d %d\n", number, errno);
                    buf[0] = 'q';
                    buf[1] = '\000';
                    break;
                }
            }
        }
    }
    close(fds_tcp[number]);
    thread[number] = 0;
}

void *client_thread_udp(void *args){
    int *tmp = args;
    int number = *tmp;
    struct sockaddr_in client;
    char buf[BUF_SIZE];
    printf("запуск процесса %d\n", number);

    while(buf[0] != 'q' || buf[1] != '\000'){
        if(recvfrom(fd_udp_active, buf, sizeof(buf), 0, (struct sockaddr *) &client, &size) == -1){
            printf("ERR RECV UDP fds№%d %d\n", number, errno);
            buf[0] = 'q';
            buf[1] = '\000';
        }
        else{
            printf("client: %s\n", buf);
            if(buf[0] != 'q' || buf[1] != '\000'){
                buf[0] = '\000';
                strcat(buf, "TIME");
                if(sendto(fd_udp_active, buf, sizeof(buf), 0, (struct sockaddr *) &client, size) == -1){
                    printf("ERR SEND  UDP fds№%d %d\n", number, errno);
                    buf[0] = 'q';
                    buf[1] = '\000';
                }
            }
        }
    }
    printf("выключение процесса %d\n", number);
    thread[number] = 0;
}

void *connection_thread(void *args){
    struct sockaddr_in server;
    fd_set rd;
    int number;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    fd_tcp = socket(AF_INET, SOCK_STREAM, 0);
    fd_udp = socket(AF_INET, SOCK_DGRAM, 0);
    fds_tcp[0] = socket(AF_INET, SOCK_STREAM, 0);
    fd_udp_active = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_port = htons(MAIN_PORT); 
    if(bind(fd_tcp, (struct sockaddr *) &server, size)){
        printf("ERR BIND TCP %d\n", errno);
    }
    else{
        listen(fd_tcp, MAX_AMOUNT_CLIENTS);
    }

    server.sin_port = htons(MAIN_PORT+1); 
    if(bind(fd_udp, (struct sockaddr *) &server, size)){
        printf("ERR BIND udp %d\n", errno);
    }

    server.sin_port = htons(MAIN_PORT+2); 
    if(bind(fds_tcp[0], (struct sockaddr *) &server, size)){
        printf("ERR BIND TCP %d\n", errno);
    }
    else{
        listen(fds_tcp[0], MAX_AMOUNT_CLIENTS);
    }

    server.sin_port = htons(MAIN_PORT+3); 
    if(bind(fd_udp_active, (struct sockaddr *) &server, size)){
        printf("ERR BIND udp %d\n", errno);
    }

    int fd_tmp;
    while(ifexit != 'q'){
        FD_ZERO(&rd);
        FD_SET(fd_tcp, &rd);
        FD_SET(fd_udp, &rd);

        if(select(fd_udp + 1, &rd, NULL, NULL, NULL) == -1){
            printf("ERR select %d", errno);
        }
        else{
            for(int i = 1; i <= MAX_AMOUNT_CLIENTS; i++){
                if(thread[i] == 0){
                    number = i;
                    if(FD_ISSET(fd_tcp, &rd)){
                        fd_tmp = accept(fd_tcp, NULL, &size);
                        close(fd_tmp);
                        printf("TCP connect\n");
                        pthread_create(&thread[number], NULL, client_thread_tcp, (void *)&number);
                    }
                    if(FD_ISSET(fd_udp, &rd)){
                        if(recvfrom(fd_udp, (char *) &fd_tmp, 1, 0, NULL, &size) == -1){
                            printf("ERR RECV UDP fds№%d %d\n", number, errno); 
                        }
                        printf("UDP connect\n");
                        pthread_create(&thread[number], NULL, client_thread_udp, (void *)&number);
                    }
                    break;
                }
            }
        }
    }
}

int main(){
    pthread_create(&thread[0], NULL, connection_thread, NULL);

    printf("q - принудительный выход\n");
    while(ifexit != 'q'){
        scanf("%c", &ifexit); 
    }

    pthread_cancel(thread[0]);
    for(int i = 1; i <= MAX_AMOUNT_CLIENTS; i++){
        if(fds_tcp[i])
            close(fds_tcp[i]);
        if(thread[i])
            pthread_cancel(thread[i]);
    }
    close(fds_tcp[0]);
    close(fd_udp_active);
    close(fd_tcp);
    close(fd_udp);

    return 0;
}