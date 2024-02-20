#include "main.h" 
#include <string.h>

extern struct str_func *str_array;
extern int counter; 
//void* handle;

int (*func_ptr_int)(int, int);
double (*func_ptr_double)(double, double);
void (*func_ptr_void)();
int (*first_func)(int, char*, char*, char*);

void print_menu(){
    printf("\n 0 Добавить плагин \n 1 Выход\n");
    for(int i = 0; i < counter; i++){
        printf("\n %d %s", i+2, str_array[i].func_name);
    }
    printf("\n      INPUT < ");
}

int use_plagin(int number){
    number -= 2;

    if(str_array[number].data_type == '0')
    {
        func_ptr_void = str_array[number].addr_func;
        func_ptr_void();    
        return 0;
    }
    else{
        int tmp, result;
        printf("\n  Введите два операнда операции через Enter\n");
        printf("\n      INPUT < операнд а = ");
        if(str_array[number].data_type == '1'){
            int a, b;
            scanf("%d", &a);
            scanf("%c", (char *)&tmp);
            printf("\n      INPUT < операнд b = ");
            scanf("%d", &b);
            scanf("%c", (char *)&tmp);
            func_ptr_int = str_array[number].addr_func;
            printf("\n Result = %d\n", func_ptr_int(a, b));
            return 0;
        }
        else if(str_array[number].data_type == '2'){
            double a, b;
            scanf("%lf", &a);
            scanf("%c", (char *)&tmp);
            printf("\n      INPUT < операнд b = ");
            scanf("%lf", &b);
            scanf("%c", (char *)&tmp);
            func_ptr_double = str_array[number].addr_func;
            printf("\n Result = %f\n", func_ptr_double(a, b)); 
            return 0;
        }
        else{
            printf("\n   !!!   Операцию не удалось выполнить   !!!\n");
            return 1;
        }
    }  
}

int plagin_copy_protection(void* handle){
    for(int i = 0; i < counter; i++){
        if(str_array[i].handle == handle)
            return 1;
    }
    return 0;
}

int add_plagin(){ 
    short tmp;
    void* handle;
    char name_plagin[10], fullname_plagin[16] = {"lib"};

    printf("\n Введите имя плагина в папке plagins");
    printf("\n      INPUT < ");
    fgets(name_plagin, 10, stdin);
    delete_enter(name_plagin);
    strcat(name_plagin, ".so");
    strcat(fullname_plagin, name_plagin);  

    handle = dlopen(fullname_plagin, RTLD_LAZY);
    if(!handle){ 
        return 1;
    }
    if(!plagin_copy_protection(handle)){
        first_func = dlsym(handle, "first_func");

        int local_counter = 0;
        char name_func[18], func[18], data_type;
        while(1){ 
            tmp = first_func(local_counter, name_func, func, &data_type);
            if(tmp == 2){
                str_array[counter].data_type = data_type;
                for(int i = 0; i < 18; i++)
                    str_array[counter].func_name[i] = name_func[i];
                str_array[counter].addr_func = dlsym(handle, func);
                str_array[counter].handle = handle;
                local_counter++;
                counter++;
                str_array = realloc(str_array, (counter + 1) * sizeof(struct str_func));      
            }
            else if(tmp == 0){
                break;
            }
            else if(tmp == 1){
                return 1;
            }
        }
    }
    else{
        printf("\n !!!   Похоже вы уже добавили этот плагин !!! \n");
    }
    
    return 0;
}

void delete_enter(char* name){
    char *verification_pointer;
    verification_pointer = name;
    for (int i = 0; i < 18; i++){
        if(*verification_pointer == '\n')
            *verification_pointer = '\0'; 
        verification_pointer++;
    }
}