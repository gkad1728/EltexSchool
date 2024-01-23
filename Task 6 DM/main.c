#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "lib.h"

int main(){
    struct abonent *str;
    int number, counter = -1, tmp;

    while(1){
        printf("\n   1) Добавить абонента\n   2) Удалить абонента\n   3) Поиск абонентов по имени\n   4) Вывод всех записей\n   5) Выход\n Input --> ");
        scanf("%d", &number);
        scanf("%c", (char *)&tmp);

        switch(number){

            case 1:
                if(counter > -1){
                    str = realloc(str, counter * sizeof(struct abonent) + sizeof(struct abonent));
                    if(!str){
                        printf("Error DM (realloc)");
                        free(str);
                        return 1;
                    }
                }
                else{
                    str = malloc(sizeof(struct abonent));
                    if(!str){
                        printf("Error DM (malloc)");
                        free(str);
                        return 1;
                    }
                    counter = 0;
                }
                add(str[counter].name, str[counter].second_name, str[counter].tel);
                printf("\n%s %s added\n", str[counter].name, str[counter].second_name);
                counter++;
                break;

            case 2:
                if(counter > -1){
                    if(del(str, counter)){
                        counter--;
                        if(counter != 0)
                            str = realloc(str, counter * sizeof(struct abonent));
                        else{
                            free(str);
                            counter = -1;
                        }
                        if(!str){
                            printf("Error DM (realloc)");
                            free(str);
                            return 1;
                        }
                    }

                }
                else{
                    printf("\nСписок абонентов пуст\n");
                }
                break;

            case 3:
                search(str, counter);
                break;

            case 4:
                list_str(counter, str);
                break;


            case 5:
                if(counter != -1)
                    free(str);
                return 0;
        }
    }
    return 1;
} 

