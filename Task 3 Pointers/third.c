#include <stdio.h> 

int main(){
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *pointer = array;

    while(*pointer < 10){
        printf("%d ", *pointer); 
        pointer++;
    } 
    printf("%d\n", *pointer);
    
    return 0;
}

 