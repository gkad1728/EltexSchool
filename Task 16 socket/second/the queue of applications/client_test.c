#include "lib.h"

int counter_error = 0;

void *light_test(void *args){
    int fd, number, *tmp;
    tmp = args;
    number = *tmp;
    struct sockaddr_in server, client;
    char buf[BUF_SIZE]; 
    socklen_t size = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_DGRAM, 0);   

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(MAIN_PORT);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;

    if(bind(fd, (struct sockaddr *) &client, size) == -1){
        printf("ERR BIND %d client №%d", errno, number);
        counter_error++;
        close(fd);  
    }
    else{
        buf[0] = '\000';
        strcat(buf, "Hi");
        if(sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *) &server, size) == -1){
            printf("ERR SEND client №%d %d\n", number, errno);
            close(fd);  
            counter_error++;
        }

        buf[0] = '\000';
        if(recvfrom(fd, buf, sizeof(server.sin_port), 0, (struct sockaddr *) &server, &size) == -1){
            printf("ERR Connect client № %d %d \n", number, errno);
            close(fd);  
            counter_error++;
        }
        else{
            printf("client №%d connected\n", number);
            for(int i = 0; i < 5; i++){
                buf[0] = '\000';
                if(sendto(fd, "HI test", sizeof("HI test"), 0, (struct sockaddr *) &server, size) == -1){
                    printf("ERR SEND client № %d %d\n", number, errno);
                    close(fd);  
                    counter_error++; 
                }
                else{
                    buf[0] = '\000';
                    if(recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *) &server, &size) == -1){
                        printf("ERR RECV client № %d %d\n", number, errno);
                        close(fd);  
                        counter_error++; 
                    }
                }
                sleep(1);
            }
            buf[0] = 'q';
            buf[1] = '\000';
            if(sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *) &server, size) == -1){
                printf("ERR SEND client № %d %d\n", number, errno);
                close(fd);  
                counter_error++; 
            }
            close(fd);
        }
    } 
    printf("client №%d disconnected\n", number);
}

void *hard_test(void *args){
    int fd, number, *tmp;
    tmp = args;
    number = *tmp;
    struct sockaddr_in server, client;
    char buf[BUF_SIZE]; 
    socklen_t size = sizeof(struct sockaddr_in);

    fd = socket(AF_INET, SOCK_DGRAM, 0);   

    memset(&server, 0, sizeof(server));
    memset(&client, 0, sizeof(client));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(MAIN_PORT);

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;

    if(bind(fd, (struct sockaddr *) &client, size) == -1){
        printf("ERR BIND %d client №%d", errno, number);
        counter_error++;
        close(fd);  
    }
    else{
        buf[0] = '\000';
        strcat(buf, "Hi");
        if(sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *) &server, size) == -1){
            printf("ERR SEND client №%d %d\n", number, errno);
            close(fd);  
            counter_error++;
        }

        buf[0] = '\000';
        if(recvfrom(fd, buf, sizeof(server.sin_port), 0, (struct sockaddr *) &server, &size) == -1){
            printf("ERR Connect client № %d %d \n", number, errno);
            close(fd);  
            counter_error++;
        }
        else{
            printf("client №%d connected\n", number);
            for(int i = 0; i < 50; i++){
                buf[0] = '\000';
                if(sendto(fd, "HI test", sizeof("HI test"), 0, (struct sockaddr *) &server, size) == -1){
                    printf("ERR SEND client № %d %d\n", number, errno);
                    close(fd);  
                    counter_error++; 
                }
                else{
                    buf[0] = '\000';
                    if(recvfrom(fd, buf, BUF_SIZE, 0, (struct sockaddr *) &server, &size) == -1){
                        printf("ERR RECV client № %d %d\n", number, errno);
                        close(fd);  
                        counter_error++; 
                    }
                } 
            }
            buf[0] = 'q';
            buf[1] = '\000';
            if(sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *) &server, size) == -1){
                printf("ERR SEND client № %d %d\n", number, errno);
                close(fd);  
                counter_error++; 
            }
            close(fd);
        }
    } 
    printf("client №%d disconnected\n", number);
}

int main(){
    int number = 1, tmp, *status;

    printf("Максимальное кол-во серверов сейчас %d\nВведите максимальное кол-во клиентов для теста: ", MAX_AMOUNT_CLIENTS);
    scanf("%d", &number);
    pthread_t thread[number]; 

    printf("start first stap test (light)\n");
    for(int i = 0; i < number; i++){ 
        pthread_create(&thread[i], NULL, light_test, (void *)&i);
        sleep(1);
    }
    for(int i = 0; i < number; i++){
        pthread_join(thread[i], (void **)&status);
    }
    printf("end first stap test error: %d\n", counter_error);

    printf("start second stap test (light)\n");
    for(int i = 0; i < number; i++){ 
        tmp = i;
        pthread_create(&thread[i], NULL, hard_test, (void *)&tmp); 
    }
    for(int i = 0; i < number; i++){
        pthread_join(thread[i], (void **)&status);
    }
    printf("end second stap test error: %d\n", counter_error);
    
    return 0;
}