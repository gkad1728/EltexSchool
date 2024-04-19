#include "Server.h"

extern WINDOW *stdscr;
WINDOW *chat_win;
WINDOW *users_win;
WINDOW *massage_win; 
extern char *ptr_server, *ptr_client;
extern int tmp;
extern sem_t *semid1, *semid2, *semid3, *semid4; 

int counter_nickname, counter_chat, counter_client = 0;
struct winsize ws;

void *thread_chat(void *args){
    while(tmp != 113){
        sem_wait(semid2); 
        for(int i = 0; ptr_server[i] != '\n' && i <= 500; i++){
            ptr_client[i] = ptr_server[i];
        }
        if(ptr_server[0] == 'C' && ptr_server[1] == 'C'){
            counter_client++;
            counter_nickname++;
            wmove(users_win, counter_nickname, 1);
            wprintw(users_win, "%s", &ptr_server[14]); //CC: connected NICK \n
        }
        if(ptr_server[0] == 'C' && ptr_server[1] == 'D' && counter_client != 0){
            counter_client--;
        } 
        wmove(chat_win, counter_chat, 1);
        wprintw(chat_win, "%s", ptr_client);
        counter_chat++;
        sem_post(semid1);
        for(int i = 0; i < counter_client; i++){
            sem_post(semid4);
            sem_wait(semid3);
        }
        ptr_server[0] = '\000';
        ptr_client[0] == '\000';

        wrefresh(chat_win);  
        wrefresh(users_win);  
    }
}

void sig_winch(int signo){ 
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);  
    refreshwin(); 
}

void init_graf(){
    initscr();
    signal(SIGWINCH, sig_winch);
    cbreak();
    curs_set(0); 
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_GREEN); 
    refresh();

    refreshwin();  
}

void refreshwin(){
    win_del();
    counter_chat = 1;
    counter_nickname = 1; 

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws); 
    chat_win = newwin(ws.ws_row - 5, ws.ws_col - 22, 0, 0);
    users_win = newwin(ws.ws_row - 5, 22, 0, ws.ws_col - 22);
    massage_win = newwin(5, ws.ws_col, ws.ws_row - 5, 0);
    wbkgd(chat_win, COLOR_PAIR(1));
    wbkgd(users_win, COLOR_PAIR(1));
    wbkgd(massage_win, COLOR_PAIR(2));

    wmove(chat_win, counter_chat, 1);
    
    wmove(massage_win, 1, 1);
    wprintw(massage_win, "q - quit \n c - clean"); 

    box(chat_win, 0, 0);
    box(users_win, 0, 0);
    box(massage_win, 0, 0);

    wrefresh(chat_win);
    wrefresh(users_win);
    wrefresh(massage_win);
    refresh();
}

void win_del(){
    delwin(chat_win);
    delwin(users_win); 
    delwin(massage_win);
}

void end_graf(){
    win_del();
    endwin();
}