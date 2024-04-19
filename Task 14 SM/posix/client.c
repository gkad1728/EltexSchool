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
    semid = sem_open(NAME_SEM, O_CREAT); 

    fd = shm_open(NAME_SH, O_RDWR, 0666);
    if(fd == -1){
        printf("ERR OPEN");
        return -1;
    } 
    ptr = (char *)mmap(NULL, size_sh, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    printf("%s\n", ptr);
    ptr[0] = '\000';
    strcat(ptr, "Hi");
    sem_post(semid);  

    close(fd); 
    if(sem_close(semid) == -1){
        printf("ERR ftran");
        return -1;
    } 
    return 0;

}