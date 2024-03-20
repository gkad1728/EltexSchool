#include "lib.h"

long array_trader[5], array_shopper[3];

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER, mutex2 = PTHREAD_MUTEX_INITIALIZER, mutex3 = PTHREAD_MUTEX_INITIALIZER, mutex4  = PTHREAD_MUTEX_INITIALIZER, mutex5  = PTHREAD_MUTEX_INITIALIZER;
int *ptr_mutex[] = {(int *)&mutex1, (int *)&mutex2, (int *)&mutex3, (int *)&mutex4, (int *)&mutex5};

int main(){ 

    int num_thread[3], *status;
    pthread_t threads[4];

    printf("Старт игры\n");

    for(int i = 0; i < 5; i++){                                         //Инициализация массивов
        array_trader[i] = rand() % 10000;
        printf("Магазин %d стартовый товар: %ld\n", i, array_trader[i]);
    }
    for(int i = 0; i < 3; i++){
        array_shopper[i] = rand() % 100000;
        printf("Покупатель %d стартовая потребность %ld\n", i, array_shopper[i]);
        num_thread[i] = i; 
    }                                                                   //

    for(int i = 0; i < 3; i++){                                         //Старт потоков
        pthread_create(&threads[num_thread[i]], NULL, func_shopper, &(num_thread[i]));
    } 
    pthread_create(&threads[3], NULL, func_loader, NULL);

    for(int i = 0; i < 3; i++){                                         //Конец потоков
        pthread_join(threads[num_thread[i]], (void **)&status);
    }
    pthread_join(threads[3], (void **)&status);

    printf("Конец игры\n"); 
    return 0;
}