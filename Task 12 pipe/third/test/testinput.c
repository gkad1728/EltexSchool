#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(){
    char buf;  
    while(read(0, &buf, 1) > 0){ 
        write(1, &buf, 1); 
        if(buf == '\n')
            break;
    } 
    exit(0);
}
