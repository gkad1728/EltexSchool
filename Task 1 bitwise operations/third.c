#include <stdio.h>

int main(){
    unsigned int a, b;
    printf("Enter a number: ");
    if(scanf("%d", &a) - 1){
        printf("Error: Invalid value\n");
        return -1;
    }

    printf("The first way:  ");
    b = 0;
    for(int i = 31; i >= 0; i--)
        b += (a >> i) & 1;
    printf("%d", b);

    printf("\nThe second way: ");
    b = 0;
    for(int i = 0; i < 32; i++){ 
        if ((a >> 31) & 1)
            b++;
        a = a << 1;
    }
    printf("%u\n", b); 
    return 0;
}