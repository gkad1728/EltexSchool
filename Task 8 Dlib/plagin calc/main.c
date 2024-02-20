#include "main.h"

struct str_func *str_array;
int counter = 0; 

int main(){ 
    int number; 
    int tmp;

    str_array = malloc(sizeof(struct str_func));
    if(!str_array){
        printf("\n ERROR ошибка выделения памяти под структуру");
        free(str_array);
        return 1;
    }

    while(1){
        print_menu(); 

        scanf("%d", &number);
        scanf("%c", (char *)&tmp);

        if((number <= counter+1) && counter > 0 && number > 1){
            if(use_plagin(number)) 
                printf("\n Ошибка при использовании плагина\n");
        }
        else if(number == 0){
            if(!add_plagin())
                printf("\n Плагин успешно добавлен\n");
            else 
                printf("\n Ошибка при добавлении плагина\n");
        }
        else if(number == 1){
            for(int i = 0; i < counter; i++){
                dlclose(str_array[i].handle);
            }
            free(str_array);
            return 0;
        }
        else{
            printf("\n Нет такого пункта в меню. Попробуйте ещё раз, но внимательнее");
        }
    }
    return 1;
}