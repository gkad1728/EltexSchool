#include <stdio.h>
#include <signal.h>

int a = 1;

void func1(int sig){
    printf("Сигнал получен signal\n"); 
    a = 0;
}

void func2(int signum){
    printf("Сигнал получен sigaction\n");
    a = 0;
}

int main(){
    signal(SIGUSR1, func1);
    
    struct sigaction sa;
    sa.sa_handler = func2;
    sigaction(SIGUSR2, &sa, NULL);

    while(a){
        if(a);
    }
}