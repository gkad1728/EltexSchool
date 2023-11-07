#include <stdio.h>
#define N 3

int main(){
    int array[N][N];

    printf("The first way: \n");
    for (int i = 1; i <= N*N; i++){
        array[i / N][i % N] = i;
        printf("%d %c", array[i / N][i % N], 10 * (i % N == 0));
    }

    printf("The second way: \n");
    for (int i = 0; i < N; i++){
        for (int k = 1; k <= N; k++){
            array[i][k] = (i * N) + k;
            printf("%d ", (i * N) + k);
        }
        printf("\n");
    }
    return 0;
}