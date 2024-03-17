#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t child_pid;
    int status;

    child_pid = fork();
    if(child_pid == 0){
        printf("Child pid = %d\n", getpid());
        exit(4);
    }
    else{
        printf("Parent pid = %d\n", getpid());
        wait(&status);
    }
    return 0;
}