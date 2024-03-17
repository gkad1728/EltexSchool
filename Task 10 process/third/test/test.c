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
        execl("main", " ",NULL);
    }
    else{
        wait(&status);
        printf("status = %d\n", WEXITSTATUS(status));
    }
}