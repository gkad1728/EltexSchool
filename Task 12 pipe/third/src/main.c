#include "main.h" 
#define MAX_BUF_TEXT 255

char buf[MAX_BUF_TEXT], massage[MAX_BUF_TEXT];
char *r_path, *l_path;
struct dirent **r_namelist;
struct dirent **l_namelist;
int r_n, l_n, number = 3, tmp; 

int main(){
    int counter, text_counter = 0, exit = 0;
    massage[0] = '\000';

    path_get(&r_path);
    path_get(&l_path);
    r_n = scandir(r_path, &r_namelist, 0, alphasort);
    l_n = scandir(l_path, &l_namelist, 0, alphasort);
    
    DV_init();
    while(exit != 1){
    counter = getch(); 
    
    switch (counter){
        case 66:
            if(number % 2 == 1){
                if(number / 2 < (l_n -1)){
                    number += 2;
                }
            }
            else{
                if(number / 2 < r_n - 1){
                    number += 2;
                }
            }
            break;
        case 65:
            if(number > 3)
                number -= 2;
            break;
        case 9:
            if(number % 2 == 1)
                number = 2;
            else
                number = 3;
            break;
        case 10: 
            if(buf[0] == 'c'){
                buf[0] == '\000';

            }
            else if((buf[0] == 'e' && buf[1] == 'x' && buf[2] == 'i' && buf[3] == 't') || buf[0] == 'q'){ 
                exit = 1; 
            } 
            else if(buf[0] == '/'){
                tmp = file_search();
                for(int i = 0; buf[i] != '\000'; i++){
                    if(buf[i] == '|')
                        tmp = -1;
                } 
                if(tmp == -1){
                    if(number % 2 == 0){
                        DV_end();
                        redirecting_output(r_n, r_namelist, r_path); 
                        getch();
                        DV_init();
                    }
                    else{    
                        DV_end();
                        redirecting_output(l_n, l_namelist, l_path);
                        getch();
                        DV_init();
                    }
                }
                else if(tmp){
                    massage[0] = '\000';
                    strcat(massage, "open file");
                    number = (tmp * 2) + (number % 2);
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
                            getch();
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
                            getch();
                            DV_init();
                        }
                    }  
                }
                else{
                    massage[0] = '\000';
                    strcat(massage, "void file"); 
                }
                buf[0] = '\000';
                text_counter = 0;
            }
            else if(buf[0] == '\000'){
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
                        getch();
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
                        getch();
                        DV_init();
                    }
                }  
            }
            else{
                massage[0] = '\000';
                strcat(massage, "input not empty");
            }
            break;
        case 127:
            if(text_counter > 0){
                text_counter -= 1;
                buf[text_counter] = '\000';
            } 
            else{
                buf[0] = '\000';
                text_counter = 0;
            }
            break;
        case 27:
            break;
        default:
            if(counter > 39 && counter < 127 && counter != 91){
                buf[text_counter] = counter;
                text_counter++;
                buf[text_counter] = '\000';
            }
            
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
