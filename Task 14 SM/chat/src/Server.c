#include "Server.h"                 //sem 1 - Возможность клиентам отправить сообщение
char *ptr_server, *ptr_client;      //sem 2 - Счетчик отправленных и ожидающих обработки сообщений от клиента
sem_t *semid1, *semid2, *semid3, *semid4;    //sem 3 - Проверка отправленных сообщений перед очисткой клиентской памяти
int tmp = 0;

int main(){
    int fd1, fd2;
    pthread_t thread;
    int status;
    semid1 = sem_open(NAME_SEM1, O_CREAT, 0666, 0);
    semid2 = sem_open(NAME_SEM2, O_CREAT, 0666, 0);
    semid3 = sem_open(NAME_SEM3, O_CREAT, 0666, 0);
    semid4 = sem_open(NAME_SEM4, O_CREAT, 0666, 0);
    fd1 = shm_open(NAME_SH1, O_RDWR | O_CREAT, 0666);
    fd2 = shm_open(NAME_SH2, O_RDWR | O_CREAT, 0666);
    if(fd1 == -1 || fd2 == -1){
        printf("ERR FD");
        return -1;
    }
    if(ftruncate(fd1, size_sh) == -1 || ftruncate(fd2, size_sh) == -1){
        printf("ERR ftran");
        return -1;
    }
    ptr_client = (char *)mmap(NULL, size_sh, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    ptr_server = (char *)mmap(NULL, size_sh, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);

    init_graf(); 
    sem_post(semid2);  
    pthread_create(&thread, NULL, thread_chat, NULL);
    strcat(ptr_server, "server: START CHAT\n");
    while(tmp != 113){
        tmp = getch();
        if(tmp == 99)
            refreshwin();
    }

    ptr_server[0] = '\000';
    sem_post(semid2);  
    strcat(ptr_server, "server: END CHAT\n");
    refreshwin();
    for(int i = 0; i < 10; i++){
        sem_post(semid1);
        sem_post(semid2);
        sem_post(semid3);
        sem_post(semid4);
    }
    pthread_join(thread, (void *)&status);
    sleep(2);

    end_graf();
    close(fd1);
    close(fd2);
    if(munmap(ptr_server, size_sh)){
        printf("ERR munmap");
        return -1;
    }
    if(munmap(ptr_client, size_sh)){
        printf("ERR munmap");
        return -1;
    }
    if(shm_unlink(NAME_SH1) == -1 || shm_unlink(NAME_SH2) == -1){
        printf("ERR unlink");
        return -1;
    }
    if(sem_close(semid1) == -1 || sem_close(semid2) == -1 || sem_close(semid3) == -1 || sem_close(semid4) == -1){
        printf("ERR sem close");
        return -1;
    }
    if(sem_unlink(NAME_SEM1) == -1 || sem_unlink(NAME_SEM2) == -1 || sem_unlink(NAME_SEM3) == -1 || sem_unlink(NAME_SEM4) == -1){
        printf("ERR sem unlink");
        return -1;
    }
    return 0;

}
