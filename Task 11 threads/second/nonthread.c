#include <stdio.h> 

#define LIMIT 300000000

int main(){ 
    long a = 0;
    for(long i = 0; i < LIMIT; i++)
        a++;
    printf("%ld\n", a);
    return 0;
}