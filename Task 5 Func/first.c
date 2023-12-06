#include <stdio.h>

struct abonent{
    char name[10];
    char second_name[10];
    char tel[10];
};

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
        if(*verification_pointer == '\n')
            *verification_pointer = '\0'; 
        verification_pointer++;
    }
}

void delete(char *ptr){
    for (int i = 0; i < 30; i++){ 
        *ptr = 0;
        ptr++;
    }
}

void search(struct abonent str[], int counter){
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

void list_str(int counter, struct abonent str[]){
    printf("\nСписок всех абонентов: \n");
    for(int i = 0; i < counter; i++){
        printf("    %d %s %s: %s\n", i + 1, str[i].second_name, str[i].name, str[i].tel);
    }
}

int main(){
    struct abonent str[100];
    int number, counter = 0, tmp; 

    while(1){
        printf("\n   1) Добавить абонента\n   2) Удалить абонента\n   3) Поиск абонентов по имени\n   4) Вывод всех записей\n   5) Выход\n Input --> ");
        scanf("%d", &number);
        scanf("%c", (char *)&tmp);
        
        switch(number){
            case 1:
                if(counter < 100){
                    add(str[counter].name, str[counter].second_name, str[counter].tel);;
                    counter++;
                    }
                else
                    printf("Абонентский справочник переполнен\n");
                break;
            case 2:
                if(counter != 0){
                    counter--;
                    delete(str[counter].name);
                    printf("\nАбонент %s %s удалён из справочника\n", str[counter].second_name, str[counter].name);
                }
                else
                    printf("Абонентский справочник пуст\n");
                break;
            case 3:
                search(str, counter);
                break;
            case 4:
                list_str(counter, str);
                break;
            case 5:
                return 0;
        }
    }
    return 1;
}