#include "Server.h"
sem_t *semid1, *semid2, *semid3, *semid4; 
char *ptr_server, *ptr_client;   
int tmp = 0;
int exits = 0;
char massage_buf[100]; 

extern WINDOW *massage_win;

int main(){
    int fd1, fd2, text_counter = 0;
    pthread_t thread;
    int status;

    char name[50];
    printf("Введите ваше имя для присоединения к чату(Макс 50 сим): ");
    fgets(name, 50, stdin);

    semid1 = sem_open(NAME_SEM1, O_CREAT);
    semid2 = sem_open(NAME_SEM2, O_CREAT);
    semid3 = sem_open(NAME_SEM3, O_CREAT);
    semid4 = sem_open(NAME_SEM4, O_CREAT);
    fd1 = shm_open(NAME_SH1, O_RDWR, 0666);
    fd2 = shm_open(NAME_SH2, O_RDWR, 0666);
    if(fd1 == -1 || fd2 == -1){
        printf("ERR FD");
        return -1;
    }
    ptr_client = (char *)mmap(NULL, size_sh, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    ptr_server = (char *)mmap(NULL, size_sh, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);

    init_graf();
    sem_post(semid2); 
    sem_wait(semid1);
    strcat(ptr_server, "CC: connected ");
    strcat(ptr_server, name);

    pthread_create(&thread, NULL, thread_chat, NULL);

    while(exits != 1){
        tmp = getch();

        switch(tmp){
            case 10:
                if(massage_buf[0] == '/'){
                    if(massage_buf[1] == 'q')
                        exits = 1;
                }
                else{ 
                    sem_post(semid2); 
                    sem_wait(semid1);
                    strcat(ptr_server, name);
                    ptr_server[strlen(ptr_server) - 1] = '\000';
                    strcat(ptr_server, ": ");
                    strcat(ptr_server, massage_buf);   
                    massage_buf[0] = '\000';
                    text_counter = 0;
                }
                break;
            case 127:
                if(text_counter > 0){
                    text_counter -= 1;
                    massage_buf[text_counter] = '\000';
                } 
                else{
                    massage_buf[0] = '\000';
                    text_counter = 0;
                }
                break;
            default:
                if(tmp > 39 && tmp < 127 && tmp != 91){
                    massage_buf[text_counter] = tmp;
                    text_counter++;
                    massage_buf[text_counter] = '\000';
                    wrefresh(massage_win);
                }
        }
        refmas();
    }

    sem_post(semid2); 
    sem_wait(semid1);
    strcat(ptr_server, "CC: Disconnected ");
    strcat(ptr_server, name);

    pthread_join(thread, (void *)&status);
    end_graf();
    close(fd1);
    close(fd2);

    if(sem_close(semid1) == -1 || sem_close(semid2) == -1 || sem_close(semid3) == -1){
        printf("ERR sem close");
        return -1;
    }
    return 0;
}