#include "Server.h"

extern WINDOW *stdscr;
WINDOW *chat_win;
WINDOW *users_win;
WINDOW *massage_win; 
extern char *ptr_server, *ptr_client;
extern sem_t *semid1, *semid2, *semid3, *semid4; 
extern int exits;
extern char massage_buf[100];

int counter_nickname, counter_chat, counter_client = 0;
struct winsize ws;

void *thread_chat(void *args){
    while(exits != 1){
        sem_wait(semid4);
        wmove(chat_win, counter_chat, 1);
        counter_chat++;
        wprintw(chat_win, "%s", ptr_client);
        if(ptr_client[0] == 'C' && ptr_client[1] == 'C'){
            wmove(users_win, counter_nickname, 1);
            counter_nickname++;
            wprintw(users_win, "%s", &ptr_client[14]);
        }
        if(ptr_client[8] == 'E' && ptr_client[9] == 'N' && ptr_client[10] == 'D'){
            exits = 1;
        }
        sem_post(semid3);
        wrefresh(chat_win);  
        wrefresh(users_win); 
    }
}

void refmas(){
    delwin(massage_win);
    massage_win = newwin(5, ws.ws_col, ws.ws_row - 5, 0);
    wbkgd(massage_win, COLOR_PAIR(2)); 
    box(massage_win, 0, 0);
    wmove(massage_win, 2, 1);
    wprintw(massage_win, "/q - quit");
    wmove(massage_win, 1, 1);
    wprintw(massage_win, "%s", massage_buf);
    wrefresh(massage_win);
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
    curs_set(1); 
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_GREEN); 
    refresh();
    
    refreshwin();  
}

void refreshwin(){
    win_del();

    counter_chat = 1; 

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws); 
    chat_win = newwin(ws.ws_row - 5, ws.ws_col - 22, 0, 0);
    users_win = newwin(ws.ws_row - 5, 22, 0, ws.ws_col - 22); 
    wbkgd(chat_win, COLOR_PAIR(1));
    wbkgd(users_win, COLOR_PAIR(1)); 

    box(chat_win, 0, 0);
    box(users_win, 0, 0); 

    move(ws.ws_row - 4, 1);

    wrefresh(chat_win);
    wrefresh(users_win); 
    refmas();
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