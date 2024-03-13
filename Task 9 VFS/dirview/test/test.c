#include <stdlib.h>
#include <stdio.h>
#include <dirent.h> -
#include <unistd.h>
#include <limits.h>  
#include <string.h> 

int main(){
   char *path; 
   path = malloc(PATH_MAX); 
   if(getcwd(path, PATH_MAX)){
      printf("Текущая директория: %s\n", path);
   }
   else{
      printf("Ошибка определения директории\n");
   } 
   path = realloc(path, strlen(path));

   struct dirent **namelist;
   int n;  
   n = scandir(path, &namelist, 0, alphasort);
   if (n < 0)
      perror("scandir");
   else {
      while(n--) {
         printf("%s ", namelist[n]->d_name); 
         printf("%ld ", strlen(namelist[n]->d_name));  
         printf("%d \n", namelist[n]->d_type);
         free(namelist[n]);
      }
      free(namelist);
   }

   free(path);
   return 0;
   
}