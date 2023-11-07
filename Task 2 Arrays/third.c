#include <stdio.h>
#define N 5

int main(){
    int array[N][N];
    for (int i = 0; i < N*N; i++){
        array[i / N][i % N] = (i % N) < N - (i / N);
        printf("%d %c", array[i / N][i % N], 10 * ((i + 1) % N == 0));
    }    
    return 0;
}