#include <stdio.h>

int main(){
    unsigned int a;
    printf("Enter a number: ");
    if(scanf("%d", &a) - 1){
        printf("Error: Invalid value\n");
        return -1;
    }
    
    printf("The first way:  ");
    for(int i = 31; i >=0; i--)
        printf("%d", (a >> i) & 1);
    

    printf("\nThe second way: ");
    for(int i = 0; i < 32; i++){
        printf("%u", ((a >> 31) & 1)); 
        a = a << 1;
    }
    printf("\n"); 
    return 0;
}