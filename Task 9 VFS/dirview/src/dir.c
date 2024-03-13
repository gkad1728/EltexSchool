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