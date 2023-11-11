#include <sys/time.h> 
#include <stdio.h>
#include <unistd.h>
#define N 5

int main(){
    struct timeval start_time, end_time; 
    double time_used; 
    gettimeofday(&start_time, NULL); 

    int array[N][N];
    for (int i = 0; i < N*N; i++){
        array[i / N][i % N] = (i % N) < N - (i / N);
        printf("%d %c", array[i / N][i % N], 10 * ((i + 1) % N == 0));
    }
    //sleep(1);

    gettimeofday(&end_time, NULL);
    time_used = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0; 
    printf("\nTime = %f seconds\n", time_used);    

    return 0;
}