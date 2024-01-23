#include <stdio.h>
#include "lib.h"

void add(char *name, char *s_name, char *tel){
    printf("\nВведите имя абонента: ");
    fgets(name, 10, stdin);
    printf("Введите фамилию абонента: ");
    fgets(s_name, 10, stdin);
    printf("Введите номер телефона абонента: ");
    fgets(tel, 10, stdin);

    char *verification_pointer;
    verification_pointer = name;   //Удаление символов перевода строки
    for (int i = 0; i < 30; i++){
        if(*verification_pointer == '\n'){
            *verification_pointer = '\0'; 
            break;
        }
        verification_pointer++;
    }
    verification_pointer = s_name;   //Удаление символов перевода строки
    for (int i = 0; i < 30; i++){
        if(*verification_pointer == '\n'){
            *verification_pointer = '\0'; 
            break;
        }
        verification_pointer++;
    }
    verification_pointer = tel;   //Удаление символов перевода строки
    for (int i = 0; i < 30; i++){
        if(*verification_pointer == '\n'){
            *verification_pointer = '\0'; 
            break;
        }
        verification_pointer++;
    }
}

int del(struct abonent *str, int counter){
    char tmp_search[10];
    int tmp, number;
    printf("\nВведите имя абонента для удаления: ");
    fgets(tmp_search, 10, stdin); 

    for (int i = 0; i < counter; i++){
        for(int y = 0; str[i].name[y] == tmp_search[y]; y++){
            if(str[i].name[y+1] == '\0'){ 
                printf("%s %s: %s\n", str[i].second_name, str[i].name, str[i].tel);
                printf("1. Удалить \n2. Следующий абонент с подходящим именем\n3.Для выхода введите что угодно кроме 1 и 2\n --->");
                scanf("%d", &number);
                scanf("%c", (char *)&tmp);
                if(number == 1){
                    counter--;
                    printf("\nАбонент %s %s удалён из справочника\n", str[i].second_name, str[i].name);
                    for(int p = 0; p < 9; p++){
                        str[i].name[p] = str[counter].name[p];
                        str[i].second_name[p] = str[counter].second_name[p];
                        str[i].tel[p] = str[counter].tel[p];
                    }
                    return 1;
                }
                if(number == 2){
                    break;
                }
                else{
                    printf("\nВы покинул функцию удаления\n");
                    return 0;
                } 
            }
        }
    }
 
    printf("    Нет подходящий абонентов\n");
    return 0;
}

void search(struct abonent *str, int counter){
    char tmp_search[10];
    int tmp;
    printf("\nВведите имя абонента: ");
    fgets(tmp_search, 10, stdin);
    printf("По вашему запросу подходят: \n");

    for (int i = 0; i < counter; i++){
        for(int y = 0; str[i].name[y] == tmp_search[y]; y++){
            if(str[i].name[y+1] == '\0'){
                printf("%s %s: %s\n", str[i].second_name, str[i].name, str[i].tel);
                tmp = 1;
                break;
            }
        }
    }
    if(tmp != 1)
        printf("    Нет подходящий абонентов\n");
}

void list_str(int counter, struct abonent *str){
    printf("\nСписок всех абонентов: \n");
    for(int i = 0; i < counter; i++){
        printf("    %d %s %s: %s\n", i + 1, str[i].second_name, str[i].name, str[i].tel);
    }
}