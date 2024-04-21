#include <stdio.h>
#include <signal.h>

int a = 1; 

void func(int signum){
    printf("Сигнал получен sigaction\n");
    a = 0;
}

int main(){  
    struct sigaction sa;
    sa.sa_handler = func;

    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, 2);
    sigprocmask(SIG_BLOCK, &set, NULL);

    sigaction(SIGUSR1, &sa, NULL);

    while(a){
        if(a);
    }
}