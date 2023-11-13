#include <stdio.h>
#define N 20
#define M 3

int main(){ 
    char array[N + 2], subarray[M + 2], 
    *pointer_array = array, *pointer_subarray = subarray; 

    printf("Enter array of characters to the line(up to %d characters) :", N);
    fgets(array, N + 2, stdin);
    printf("Enter subarray of characters in a string (up to %d characters) : ", M);
    fgets(subarray, M + 2, stdin); 
 
    while(*pointer_array != 10){ //10 = "\n"

        if(*pointer_array == *pointer_subarray){
            pointer_subarray++;

            if(*pointer_subarray == 10){
                pointer_array = pointer_array - M + 1;
                
                printf("address of the first character = %p\naddress of the beginning of the substring = %p\nThe substring starts with the fifth character %ld\n", array, pointer_array, pointer_array - array);
                return 0;
            }
        }
        else
            pointer_subarray = subarray;
        pointer_array++;
    }

    pointer_array = NULL;
    printf("Substring not found\n");
    return 0;
}