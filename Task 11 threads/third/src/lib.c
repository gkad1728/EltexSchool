#include "lib.h"

extern pthread_mutex_t mutex[5];
extern long array_trader[5], array_shopper[3];
short array_traderlock[] = {0, 0, 0, 0, 0}; 
extern int *ptr_mutex[5];
int requirement = 3;

void *func_shopper(void *args){
    int *num_shopper = (void *)args;
    while(array_shopper[*num_shopper] > 0){
        for(int i = 0; i < 5; i++){
            if(array_traderlock[i] == 0 && array_trader[i] != 0){
                pthread_mutex_lock((pthread_mutex_t *)ptr_mutex[i]);
                array_traderlock[i] = 1;

                printf("Покупатель %d заходит в магазин %d Потребность %ld Предложение %ld\n", *num_shopper, i, array_shopper[*num_shopper], array_trader[i]);
                if(array_trader[i] < array_shopper[*num_shopper]){
                    array_shopper[*num_shopper] -= array_trader[i];
                    array_trader[i] = 0;
                }   
                else{
                    array_trader[i] -= array_shopper[*num_shopper];
                    array_shopper[*num_shopper] = 0;
                }
                printf("Покупатель %d Выходит из магазина %d Потребность %ld Предложение %ld\n", *num_shopper, i, array_shopper[*num_shopper], array_trader[i]);

                array_traderlock[i] = 0;
                pthread_mutex_unlock((pthread_mutex_t *)ptr_mutex[i]);
                break;
            }
        } 
        sleep(2);
    }
    requirement --;
    printf("Покупатель %d удовлетворил потребность %ld\n", *num_shopper, array_shopper[*num_shopper]);
}

void *func_loader(void *args){
    while(requirement){
        for(int i = 0; i < 5; i++){
            if(array_traderlock[i] == 0){
                pthread_mutex_lock((pthread_mutex_t *)ptr_mutex[i]);
                array_traderlock[i] = 1;

                array_trader[i] += 5000;

                array_traderlock[i] = 0;
                pthread_mutex_unlock((pthread_mutex_t *)ptr_mutex[i]);
                break;
            }
        }
        sleep(1);
    }
    printf("Погрузчик закончил работу\n");
    for(int i = 0; i < 5; i++){
        printf("Магазин %d итог %ld\n", i, array_trader[i]);
    }
}