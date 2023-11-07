#include <stdio.h>
#define N 5

int main(){
    int array[N], a;
    for (int i = 0; i < N; i++){
        printf("Input <- ");
        scanf("%d", &a);
        array[i] = a;  
    }

    for (int i = 0; i < N / 2; i++){
        a = array[i]; 
        array[i] = array[N - i - 1];
        array[N - i - 1] = a;
    }

    printf("\nOutput: ");
    for (int i = 0; i < N; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
    return 0;
}