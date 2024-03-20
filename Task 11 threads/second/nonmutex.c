#include <stdio.h>
#include <pthread.h>

#define AMOUNT_THREAD 5
#define LIMIT 300000000

long a = 0, array[AMOUNT_THREAD];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *args){
    int *k = (void *)args;
    for(int i = 0; i < (LIMIT / AMOUNT_THREAD); i++){
        array[*k]++;
    }
}

int main(){ 
    int array_number[AMOUNT_THREAD];
    int *status;

    pthread_t thread[AMOUNT_THREAD];

    for(int i = 0; i < AMOUNT_THREAD; i++){
        array_number[i] = i;
        pthread_create(&thread[array_number[i]], NULL, thread_func, &(array_number[i]));
    }

    for(int i = 0; i < AMOUNT_THREAD; i++){
        pthread_join(thread[array_number[i]], (void **)&status);
    }

    for(int i = 0; i < AMOUNT_THREAD; i++){
        a += array[i];
    }
    printf("%ld\n", a);
    return 0;
}