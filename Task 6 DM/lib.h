#ifndef __LIB_H__
#define __LIB_H__

struct abonent{
    char name[10];
    char second_name[10];
    char tel[10];
};

void add(char *, char *, char *);
int del(struct abonent *, int);
void search(struct abonent *, int);
void list_str(int, struct abonent *);
#endif 
