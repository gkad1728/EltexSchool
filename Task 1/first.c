#include <stdio.h>

int main(){
    unsigned int a;
    printf("Enter a number: ");
    scanf("%u", &a);
  
    for(int i = 0; i < 32; i++){
        printf("%u", (a & (1 << 31)) >> 31); 
        a = a << 1;
    }
    printf("\n");
    return 0;
}