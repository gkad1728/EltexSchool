#include <stdio.h> 

int main(){
    unsigned int number, tmp;
    char *pointer = (char *)&number;
    pointer += 2;

    printf("Enter the initial number ->     ");
    scanf("%x", &number);
    printf("Enter the number to replace ->  ");
    scanf("%x", &tmp);
    printf("%x\n", number); 
    *pointer = tmp;
    printf("%x\n", number);
    return 0;
}