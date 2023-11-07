#include <stdio.h>

int main(){
    unsigned int a, b, c;
    printf("Enter a number: ");
    if(scanf("%d", &a) - 1){
        printf("Error: Invalid value\n");
        return -1;
    }
    c = a;

    printf("Enter the correct number to replace previous one(1 or 0): ");
    scanf("%d", &b);
    
    printf("The original number :   %u ", a);
    for(int i = 0; i < 32; i++){
        printf("%u", ((a >> 31) & 1)); 
        a = a << 1;
    }
    c = (c & ~(1 << 2)) | b << 2;
    printf("\nModified number :       %d ", c);
    for(int i = 0; i < 32; i++){
        printf("%u", ((c >> 31) & 1)); 
        c = c << 1;
    }
    printf("\n");
    return 0;
}