#include <stdio.h>
#include <signal.h>

int a = 1;

void func(){
    printf("Получен сигнал выхода SIGUSR2\n");
    a = 0;
}

int main(){
    sigset_t set;
    int sig;
    struct sigaction sa;

    sa.sa_handler = func;
    sigaction(SIGUSR2, &sa, NULL);
    
    sigemptyset(&set);
    sigaddset(&set, 10); 
    sigprocmask(SIG_BLOCK, &set, NULL);
    
    while(a){
        sigwait(&set, &sig);
        printf("Получен сигнал SIGUSR1\n");
        
    }
}