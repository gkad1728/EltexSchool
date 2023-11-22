#include <stdio.h>

struct abonent{
    char name[10];
    char second_name[10];
    char tel[10];
};

int main(){
    struct abonent str[100];
    int number, counter = 0, tmp;
    char *verification_pointer, tmp_search[10];

    while(1){
        printf("\n   1) Добавить абонента\n   2) Удалить абонента\n   3) Поиск абонентов по имени\n   4) Вывод всех записей\n   5) Выход\n Input --> ");
        scanf("%d", &number);
        scanf("%c", (char *)&tmp);
        //fflush(stdin);
        
        switch(number){
        case 1:
            if(counter < 100){
                printf("\nВведите имя абонента: ");
                fgets(str[counter].name, 10, stdin);
                printf("Введите фамилию абонента: ");
                fgets(str[counter].second_name, 10, stdin);
                printf("Введите номер телефона абонента: ");
                fgets(str[counter].tel, 10, stdin);

                verification_pointer = str[counter].name;   //Удаление символов перевода строки
                for (int i = 0; i < 30; i++){
                    if(*verification_pointer == '\n')
                        *verification_pointer = '\0'; 
                    verification_pointer++;
                }
                counter++;
            }
            if(counter == 100)
                printf("Абонентский справочник переполнен\n");
            break;

        case 2:
            counter--;
            printf("\nАбонент %s %s удалён из справочника\n", str[counter].second_name, str[counter].name); //надо изменить удаление. добавить поиск
            verification_pointer = str[counter].name;   //Зануление
            for (int i = 0; i < 30; i++){ 
                *verification_pointer = 0; 
                verification_pointer++;
            }
            break;

        case 3:
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
            break;

        case 4:
            printf("\nСписок всех абонентов: \n");
            for(int i = 0; i < counter; i++){
                printf("    %d %s %s: %s\n", i + 1, str[i].second_name, str[i].name, str[i].tel);
            }
            break;
        case 5:   
            return 0;
        }
    }
}