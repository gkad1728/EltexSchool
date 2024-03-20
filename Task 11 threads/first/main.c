#include <stdio.h>
#include <pthread.h>

#define AMOUNT_THREAD 5

void *print_thread_number(void *args){
    int *i = (int *) args;
    printf("Thread num %d\n", *i);
}

int main(){ 
    int array_number[AMOUNT_THREAD];
    int *status;

    pthread_t thread[AMOUNT_THREAD];

    for(int i = 0; i < AMOUNT_THREAD; i++){
        array_number[i] = i;
        pthread_create(&thread[array_number[i]], NULL, print_thread_number, (void *)&array_number[i]);
    }

    for(int i = 0; i < AMOUNT_THREAD; i++){
        pthread_join(thread[array_number[i]], (void **)&status);
    }
    return 0;
}