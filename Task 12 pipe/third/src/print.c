#include "main.h"
#define BOTTOM_SIZE 3
#define AT_MOD A_BLINK | A_REVERSE
extern WINDOW *stdscr;
extern char *r_path, *l_path;
extern struct dirent **r_namelist;
extern struct dirent **l_namelist;
extern int r_n, l_n, number;
extern char buf[], massage[];

WINDOW *main_win;
 
WINDOW *rmv_name;
WINDOW *rmv_size;
WINDOW *rmv_data;
 
WINDOW *lmv_name;
WINDOW *lmv_size;
WINDOW *lmv_data;

WINDOW *bottom_win;

struct winsize ws;

void print_dir(){
    int len_tmp;
    struct stat *buf;
    char *tmp_path;

    len_tmp = strlen(l_path);
    wmove(bottom_win, 1, 1); 
    if((ws.ws_col/2) < len_tmp){
        wprintw(bottom_win, "/...%s         ", &(l_path[len_tmp - ((ws.ws_col/3)-5)]));
    }
    else    
        wprintw(bottom_win, "%s  ", l_path);
    wmove(bottom_win, 1, (ws.ws_col/2)+1);
    len_tmp = strlen(r_path);
    if((ws.ws_col/2) < len_tmp){
        wprintw(bottom_win, "/...%s         ", &(r_path[len_tmp - ((ws.ws_col/3)-5)]));
    }
    else    
        wprintw(bottom_win, " %s ", r_path); 
    wmove(bottom_win, 2, 1);
    tmp_path = malloc(PATH_MAX);
    strcat(tmp_path, r_path);
    strcat(tmp_path, "/"); 
    for(int i = 1; i < r_n; i++){ 
        if((number % 2 == 0) && (number / 2 == i)){
            wattron(rmv_name, AT_MOD);
        }
        wmove(rmv_name, i, 1);
        wmove(rmv_data, i, 1); 
        wmove(rmv_size, i, 1); 
        if(r_namelist[i]->d_type == 4)
            wprintw(rmv_name, "/");
        wprintw(rmv_name, "%s", r_namelist[i]->d_name);

        if(i > 1){    
            buf = malloc(sizeof(struct stat));
            tmp_path[strlen(r_path)+1] = '\000';
            strcat(tmp_path, r_namelist[i]->d_name); 
            stat(tmp_path, buf);
            wprintw(rmv_size, "%ld", buf->st_size); 
            wprintw(rmv_data, "%s", &(ctime(&(buf->st_mtime)))[4]);
            free(buf); 
        }
        if(number % 2 == 0 && (number / 2 == i)){
            wattroff(rmv_name, AT_MOD);
        }
    }
    free(tmp_path);
    tmp_path = malloc(PATH_MAX);
    tmp_path[0] = '\000';
    strcat(tmp_path, l_path);
    strcat(tmp_path, "/");

    for(int i = 1; i < l_n; i++){
        if((number % 2 == 1) && (number / 2 == i)){
            wattron(lmv_name, AT_MOD);
        } 
        wmove(lmv_data, i, 1);
        wmove(lmv_name, i, 1);
        wmove(lmv_size, i, 1);
        if(l_namelist[i]->d_type == 4)
            wprintw(lmv_name, "/");
        wprintw(lmv_name, "%s", l_namelist[i]->d_name);
        if(i > 1){
            buf = malloc(sizeof(struct stat));
            tmp_path[strlen(l_path)+1] = '\000';
            strcat(tmp_path, l_namelist[i]->d_name); 
            stat(tmp_path, buf);
            wprintw(lmv_size, "%ld", buf->st_size); 
            wprintw(lmv_data, "%s", &(ctime(&(buf->st_mtime)))[4]);
            free(buf); 
        } 
        if((number % 2 == 1) && (number / 2 == i)){
            wattroff(lmv_name, AT_MOD);
        }
    }
    free(tmp_path);
    
}

int file_search(){ 
    if(number % 2 == 0){
        for(int i = 1; i < r_n; i++){      
            if(buf[1] == r_namelist[i]->d_name[0]){
                for(int k = 0; k <= strlen(r_namelist[i]->d_name); k++){
                    if(buf[k+1] == r_namelist[i]->d_name[k]){
                        if(buf[k+2] == '\000' && k+1 == strlen(r_namelist[i]->d_name)){
                            return i;
                        }
                    }
                    else   
                            break;
                }
            }
        }
    }
    else{
        for(int i = 1; i < l_n; i++){      
            if(buf[1] == l_namelist[i]->d_name[0]){
                for(int k = 0; k < strlen(l_namelist[i]->d_name); k++){
                    if(buf[k+1] == l_namelist[i]->d_name[k]){
                        if(buf[k+2] == '\000' && k+1 == strlen(l_namelist[i]->d_name)){
                            return i;
                        } 
                    }
                    else   
                        break;
                }
            }
        }
    }
    return 0;
}

int redirecting_output(int n, struct dirent **namelist, char* path){
    int tmp;
    char buf1[255];
    char buf2[255];
    pid_t child_pid1, child_pid2, pipefd[2];
    char path_name1[255];
    char path_name2[255];

    for(int i = 0; i < 256; i++){
        buf1[i] = buf[i+1];
        if(buf[i+2] == '|'){
            buf1[i+1] = '\000';
            tmp = i + 2;
            break;
        }
    }
    for(int i = 0; i < 256; i++){
        buf2[i] = buf[i+1+tmp];
        if(buf[i+2+tmp] == '\000'){
            buf2[i+1] = '\000';
            break;
        }
    }

    buf[1] = '\000';
    strcat(buf, buf1);
    tmp = file_search();
    buf[1] = '\000';
    strcat(buf, buf2);

    tmp = tmp * file_search();
    if(tmp == 0){
        return -1;
    }
    if(pipe(pipefd) == -1)
        return -1; 

    path_name1[0] = '\000';
    path_name2[0] = '\000';
    strcat(path_name1, path);
    strcat(path_name1, "/");
    strcat(path_name1, buf1);
    strcat(path_name2, path);
    strcat(path_name2, "/");
    strcat(path_name2, buf2);

    child_pid1 = fork();
    if(child_pid1 == 0){ 
        dup2(pipefd[1], 1); 
        execl(path_name1, " ", NULL); 
        exit(0);
    }
    else{ 
        wait(NULL); 
        child_pid2 = fork();
        if(child_pid2 == 0){ 
            dup2(pipefd[0], 0); 
            execl(path_name2, " ", NULL);  
            exit(0);
        }
        else{
            wait(NULL);
            return 0;
        }
    }
}

void resizewin(){
    win_del();

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws); 
    main_win = newwin(ws.ws_row - BOTTOM_SIZE - 1, ws.ws_col, 0, 0); 
    wbkgd(main_win, COLOR_PAIR(1));

    rmv_name = derwin(main_win, ws.ws_row - BOTTOM_SIZE - 1, ws.ws_col / 4, 0, (ws.ws_col / 2) + 1);
    rmv_size = derwin(main_win, ws.ws_row - BOTTOM_SIZE - 1, ws.ws_col / 8, 0, (ws.ws_col / 2) + 1 + ws.ws_col / 4);
    rmv_data = derwin(main_win, ws.ws_row - BOTTOM_SIZE - 1, (ws.ws_col / 8) - 1, 0, (ws.ws_col / 2) + 1 + ws.ws_col / 4 + ws.ws_col / 8);
     
    lmv_name = derwin(main_win, ws.ws_row - BOTTOM_SIZE - 1, ws.ws_col / 4, 0, 0);
    lmv_size = derwin(main_win, ws.ws_row - BOTTOM_SIZE - 1, ws.ws_col / 8, 0, ws.ws_col / 4);
    lmv_data = derwin(main_win, ws.ws_row - BOTTOM_SIZE - 1, ws.ws_col / 8, 0, ws.ws_col / 4 + ws.ws_col / 8);

    bottom_win = newwin(BOTTOM_SIZE, ws.ws_col - 1, ws.ws_row - BOTTOM_SIZE, 0);
    wbkgd(bottom_win, COLOR_PAIR(2));

    print_dir();

    move(ws.ws_row - 1 - BOTTOM_SIZE, 1);
    for(int i = 0; i < ws.ws_col; i++)
        printw("_");

    move(ws.ws_row - 1 - BOTTOM_SIZE, 1);
    printw("output : %s input : %s", massage,buf); 

    box(rmv_size, 0, 0);
    box(rmv_name, 0, 0);
    box(rmv_data, 0, 0); 

    box(lmv_size, 0, 0);
    box(lmv_name, 0, 0);
    box(lmv_data, 0, 0);

    box(bottom_win, 0, 0);

    wrefresh(main_win); 
    wrefresh(bottom_win); 
    refresh();   
}

int dir_enter(char** path, char *name){
    if(number / 2 == 1){
        for(int i = strlen(*path); i != 0; i--){
            if((*path)[i] == '/'){
                (*path)[i] = '\000';
                break;
            }
        } 
        *path = realloc(*path, strlen(*path)); 
    }
    else{
        *path = realloc(*path, strlen(*path) + strlen(name)); 
        strcat(*path, "/");
        strcat(*path, name); 
    } 
    return 0;
}

void sig_winch(int signo){ 
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);  
    resizewin(); 
}

void DV_init(){
    initscr();
    signal(SIGWINCH, sig_winch);
    cbreak();
    curs_set(1); 
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_GREEN); 
    refresh();

    resizewin();  
}

int win_del(){
    delwin(main_win);
    delwin(bottom_win); 
    delwin(rmv_name);
    delwin(rmv_data);
    delwin(rmv_size);
    delwin(lmv_name);
    delwin(lmv_data);
    delwin(lmv_size);
}

int DV_end(){ 
    win_del();
    return endwin();
}