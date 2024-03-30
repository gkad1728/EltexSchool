#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t child_pid, pipefd[2];  

    if(pipe(pipefd) == -1){
        return 1;
    }

    child_pid = fork();
    if(child_pid == 0){
        char buf;
        close(pipefd[1]);
        while(read(pipefd[0], &buf, 1))
            write(STDOUT_FILENO, &buf, 1);
        write(STDOUT_FILENO, "\n", 1);
        close(pipefd[0]);
        exit(0);
    }
    else{
        close(pipefd[0]);
        write(pipefd[1], "Hello", 5);
        close(pipefd[1]);
        wait(NULL);
        return 0;
    }
}