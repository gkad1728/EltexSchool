#include <stdio.h>
#include "main.h"

int main(){
    int number, a, b;
    char number_tmp;

    while(1){
        printf("\n    1)Сложение\n    2)Вычитание\n    3)Умножение\n    4)Деление\n    5)Выход\n Input ---> ");
        scanf("%d", &number);
        scanf("%c", &number_tmp);

        if(number != 5){
            printf("Введите числа, над которыми нужно провести операцию\n");
            printf("Введите первый операнд a = ");
            scanf("%d", &a);
            scanf("%c", &number_tmp);
            printf("Введите второй операнд b = ");
            scanf("%d", &b);
            scanf("%c", &number_tmp);
        }

        switch(number){
            case 1:
                printf("\n      a + b = %d\n", add(a, b));
                break;
            case 2:
                printf("\n      a - b = %d\n", sub(a, b));
                break;
            case 3:
                printf("\n      a * b = %d\n", mul(a, b));
                break;
            case 4:
                printf("\n      a / b = %f\n", div(a, b));
                break;
            case 5:
                return 0;
        }
    }

    return 1;
}