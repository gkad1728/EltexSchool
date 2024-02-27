#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define SIZE 25

int main(){
    int fd, tmp;
    char WR_buf[SIZE], RD_buf[SIZE];
    
    printf("Введите строку, которую требуется записать в файл (%d символов максимум): ", SIZE);
    fgets(WR_buf, SIZE, stdin);

    fd = open("file", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if(fd == 0){
        return 1;
    }
    write(fd, WR_buf, strlen(WR_buf));
    lseek(fd, 0, SEEK_SET);
    read(fd, RD_buf, strlen(WR_buf));
    close(fd);

    printf("Вывод file  - %s\n", RD_buf); 
    return 0;
    
}