#include "Client.h"

extern WINDOW *stdscr;
WINDOW *chat_win;
WINDOW *users_win;
WINDOW *massage_win;
struct winsize ws;
extern char massage_buf[100];
extern char chat_buf[100];
extern int exits;
extern int counter_chat;
extern mqd_t mqdes_rds, mqdes_wrs;

void *thread_chat(void *args){
    unsigned int prio;  
    while(exits != 1){
        if(counter_chat > ws.ws_row - 8){
            refreshwin();
            counter_chat = 1;
        }
        if(mq_receive(mqdes_wrs, chat_buf, 150, &prio) == -1){
            wmove(massage_win, 3, 1); 
            wprintw(massage_win, "ERRR");  
            sleep(2);
        }
        else{
            wmove(chat_win, counter_chat, 1);
            wprintw(chat_win, "%s", chat_buf);
            chat_buf[0] = '\000';
            counter_chat++;  
        }  
        wrefresh(chat_win);
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