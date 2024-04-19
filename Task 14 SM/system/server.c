#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

struct msg{
  int type;
  char string [500];
};



int main(){
    int semid;
    int shmid;
    struct msg *shptr;
    key_t key;

    struct sembuf lock[2]= {{0, 0, 0}, {0, 1, 0}};
    struct sembuf unlock = {0, -1, 0};

    key = ftok("server", 1);
    shmid = shmget(key, 250, IPC_CREAT | 0666);
    key = ftok("server", 2);
    semid = semget(key, 1, IPC_CREAT | 0666);
    if(shmid == -1 || semid == -1){
        printf("Err shmget|semget\n");
        return -1;
    }
    shptr = shmat(shmid, 0, 0); 

    semop(semid, lock, 2);
    strcat(shptr->string, "Hello");
    semop(semid, lock, 2);
    printf("%s\n", shptr->string);
    semop(semid, &unlock, 1); 

    shmdt(shptr); 
    if(shmctl(shmid, IPC_RMID, 0)){
        printf("Err shmctl\n");
        return -1;
    }
    return 0;
}