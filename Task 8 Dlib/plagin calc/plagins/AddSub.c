extern int counter; 
#include <stdio.h>

int first_func(int local_counter, char* name_func, char* func, char* data_type){
    int localFF_counter = 2;
    char localFF_name_func[2][18] = {"Сложение", "Вычитание"};
    char localFF_func[2][18] = {"add", "sub"};
    char localFF_data_type[2] = {'1','1'};

    if(local_counter < localFF_counter){
        for(int i = 0; i < 18; i++){
            func[i] = localFF_func[local_counter][i];
            name_func[i] = localFF_name_func[local_counter][i];
        }
        if(localFF_data_type[local_counter] != '0' && localFF_data_type[local_counter] != '1' && localFF_data_type[local_counter] != '2')
            return 1;
        *data_type = localFF_data_type[local_counter]; 
        return 2;
    }
    if(local_counter == localFF_counter){
        return 0;
    }
}

int add(int a, int b){
    return a+b;
}

int sub(int a, int b){
    return a-b;
}