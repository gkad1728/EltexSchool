#include <stdio.h>

int main(){
    unsigned int a, b = 0;
    printf("Enter a number: ");
    scanf("%d", &a);
  
    for(int i = 0; i < 32; i++){ 
        if ((a >> 31) & 1)
            b++;
        a = a << 1;
    }
    printf("%u\n", b); 
    return 0;
}