#include "main.h" 

char *r_path, *l_path;
struct dirent **r_namelist;
struct dirent **l_namelist;
int r_n, l_n, number = 3, tmp; 

int main(){
    int counter;
    path_get(&r_path);
    path_get(&l_path);
    r_n = scandir(r_path, &r_namelist, 0, alphasort);
    l_n = scandir(l_path, &l_namelist, 0, alphasort);
    
    DV_init();
    while(counter != 113 && counter != 185){
    counter = getch();
    
    switch (counter){
        case 66:
            if(number % 2 == 1){
                if(number / 2 < (l_n -1)){
                    number += 2;
                }
            }
            else
                if(number / 2 < r_n - 1){
                    number += 2;
                }
            break;
        case 65:
            if(number > 3)
                number -= 2;
            break;
        case 9:
            if(number % 2 == 1){
                number = 2;
            }
            else
                number = 3;
            break;
        case 10:
            if(number % 2 == 1){
                if(l_namelist[number / 2]->d_type == 4){
                    dir_enter(&l_path, l_namelist[number / 2]->d_name);
                    Dir_del(l_n, l_namelist);
                    l_n = scandir(l_path, &l_namelist, 0, alphasort);
                    number = 3;
                }
                else if(l_namelist[number / 2]->d_type == 8){
                    DV_end();
                    printf("Вы открыли программу %s после ее завершения нажмите на ENTER, чтобы продолжить работу DV\n", l_namelist[number / 2]->d_name);
                    use_file(l_path, l_namelist[number / 2]->d_name);
                    //getch();
                    DV_init();
                }
            }
            else{
                if(r_namelist[number / 2]->d_type == 4){
                    dir_enter(&r_path, r_namelist[number / 2]->d_name);
                    Dir_del(r_n, r_namelist);
                    r_n = scandir(r_path, &r_namelist, 0, alphasort);
                    number = 2;
                }
                else if(r_namelist[number / 2]->d_type == 8){
                    DV_end();
                    printf("Вы открыли программу %s после ее завершения нажмите на ENTER, чтобы продолжить работу DV\n", r_namelist[number / 2]->d_name);
                    use_file(r_path, r_namelist[number / 2]->d_name);
                    //getch();
                    DV_init();
                }
            }  
            break;
    }
    resizewin();  
    }
    Dir_del(r_n, r_namelist);
    Dir_del(l_n, l_namelist);
    free(r_path);
    free(l_path); 
    DV_end();
    return 0;
}
