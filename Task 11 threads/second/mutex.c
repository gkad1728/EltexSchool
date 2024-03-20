#include <stdio.h>
#include <pthread.h>

#define AMOUNT_THREAD 5
#define LIMIT 300000000

long a = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *args){
    int i;
    for(int i = 0; i < (LIMIT / AMOUNT_THREAD); i++){
        pthread_mutex_lock(&mutex);
        a++;
        pthread_mutex_unlock(&mutex);
    }
}

int main(){ 
    int array_number[AMOUNT_THREAD];
    int *status;

    pthread_t thread[AMOUNT_THREAD];

    for(int i = 0; i < AMOUNT_THREAD; i++){
        array_number[i] = i;
        pthread_create(&thread[array_number[i]], NULL, thread_func, NULL);
    }

    for(int i = 0; i < AMOUNT_THREAD; i++){
        pthread_join(thread[array_number[i]], (void **)&status);
    }
    printf("%ld\n", a);
    return 0;
}