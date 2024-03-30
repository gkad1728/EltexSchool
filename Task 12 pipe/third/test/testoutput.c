#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
    char buf[] = {"HEllo world\n"};
    write(1, buf, strlen(buf)); 
    exit(0);
}
