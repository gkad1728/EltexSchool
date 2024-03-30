#include "main.h"

int path_get(char** path){
    *path = malloc(PATH_MAX); 
    if(getcwd(*path, PATH_MAX)){
        //printf("Текущая директория: %s\n", *path);
        *path = realloc(*path, strlen(*path));  
        return 0;
    }
    else{
        //printf("Ошибка определения директории\n");
        return 1;
    }  
}

int Dir_del(int n, struct dirent **namelist){
    while(n--){
        free(namelist[n]);
    }
    free(namelist);
}

int use_file(char* path, char* name){
    char* path_name;
    path_name = malloc(strlen(path) + strlen(name) + 2);
    path_name[0] = '\000';
    strcat(path_name, path);
    strcat(path_name, "/");
    strcat(path_name, name);
    

    pid_t child_pid;
    int status;

    child_pid = fork();
    if(child_pid == 0){
        execl(path_name, " ", NULL); 
        return 1;
    }
    else{
        wait(&status);
        if(!status)
            printf("Программа завершена неккоректно путь: %s%s", path, name);
        getch();
        free(path_name);
        return 0;
    } 
}