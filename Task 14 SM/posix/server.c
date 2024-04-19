#include <fcntl.h>         
#include <sys/stat.h>         
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h> 
#include <sys/types.h>
#define size_sh 20
#define NAME_SH "/name_sh"
#define NAME_SEM "/name_sh2"

int main(){ 
    int fd;
    char *ptr;
    sem_t *semid;
    semid = sem_open(NAME_SEM, O_CREAT, 0666, 0); 

    fd = shm_open(NAME_SH, O_RDWR | O_CREAT, 0666);
    if(fd == -1){
        printf("ERR OPEN");
        return -1;
    }
    if(ftruncate(fd, size_sh) == -1){
        printf("ERR ftran");
        return -1;
    }
    ptr = (char *)mmap(NULL, size_sh, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
    strcat(ptr, "Hello");
    sem_wait(semid); 
    printf("%s\n", ptr);



    close(fd);
    if(munmap(ptr, size_sh)){
        printf("ERR munmap");
        return -1;
    }
    if(shm_unlink(NAME_SH) == -1){
        printf("ERR ftran");
        return -1;
    }
    if(sem_close(semid) == -1){
        printf("ERR ftran");
        return -1;
    }
    if(sem_unlink(NAME_SEM) == -1){
        printf("ERR ftran");
        return -1;
    }
    return 0;

}