#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

struct str_func{
    void* addr_func;                 // Адресс функции
    void* handle;
    char data_type;                //тип функции. 0 - void, 1 - int, 2 - double. Какого типа функция такого типа оба операнда, передаваемые в функцию
    char func_name[18];             //Имя плагина. Максимальная длина названия 14.
};

//nt first_func(int, char*, char*, char*);
//int add_func(char, char, char);
void print_menu();
int use_plagin(int number);
int add_plagin();
void delete_enter(char *);
#endif 