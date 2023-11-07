#include <stdio.h>
#define N 7

int main(){ 
    int Border_Top = 1, Border_Left = 0, 
        Border_Right = N - 1, Border_Down = N - 1,
        x = 0, y = 0, array[N][N], Number = 1; 
    while (Number < N*N){
        while(x < Border_Right){
            array[y][x] = Number;
            x++;
            Number++;
        }
        Border_Right--;

        while(y < Border_Down){
            array[y][x] = Number;
            y++;
            Number++;
        }
        Border_Down--;

        while(x > Border_Left){
            array[y][x] = Number;
            x--;
            Number++;
        }
        Border_Left++;

        while(y > Border_Top){
            array[y][x] = Number;
            y--;
            Number++;
        }
        Border_Top++;
    }
    array[N / 2][N / 2] = N*N;

    for (int i = 0; i < N*N; i++)
        printf("%d %c", array[i / N][i % N], 10 * ((i + 1) % N == 0));

    return 0;
}