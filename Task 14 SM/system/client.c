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
    shmid = shmget(key, 250, 0);
    key = ftok("server", 2);
    semid = semget(key, 1, 0);
    if(shmid == -1 || semid == -1){
        printf("Err shmget|semget\n");
        return -1;
    }
    shptr = shmat(shmid, 0, 0); 

    printf("%s\n", shptr->string);
    shptr->string[0] = '\000';
    strcat(shptr->string, "Hi");
    semop(semid, &unlock, 1); 

    shmdt(shptr);
    return 0;
}