#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    pid_t child_pid, parent_pid;
    int status;

    parent_pid = fork();
    if(parent_pid == 0){
        printf("Parent 1 pid = %d\n", getpid());
        child_pid = fork();
        if(child_pid == 0){
            printf("Child 1.1 pid = %d\n", getpid());
            exit(11);
        }
        child_pid = fork();
        if(child_pid == 0){
            printf("Child 1.2 pid = %d\n", getpid());
            exit(12);
        }
        wait(&status);
        printf("status = %d\n", WEXITSTATUS(status));
        wait(&status);
        printf("status = %d\n", WEXITSTATUS(status));
        exit(1);
    }
    else{
        printf("Grandparent pid = %d\n", getpid());
        parent_pid = fork();
        if(parent_pid == 0){
            printf("Parent 2 pid = %d\n", getpid());
            child_pid = fork();
            if(child_pid == 0){
                printf("Child 2.1 pid = %d\n", getpid());
                exit(21);
            }
            wait(&status);
            printf("status = %d\n", WEXITSTATUS(status));
            exit(2);
        }
        else{
            wait(&status);
            printf("status = %d\n", WEXITSTATUS(status));
            wait(&status);
            printf("status = %d\n", WEXITSTATUS(status));
        } 
    }
    return 0;
}