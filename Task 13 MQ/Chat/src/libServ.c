#include "Server.h"

extern WINDOW *stdscr;
WINDOW *chat_win;
WINDOW *users_win;
WINDOW *massage_win;
struct winsize ws;
extern int counter_user, counter_chat, tmp;
extern char chat_buf[100]; 
extern char user_buf[50];
extern mqd_t mqdes_rds, mqdes_wrs;

void *thread_chat(void *args){
    unsigned int prio;  
    char test_array[110];
    /*if(mq_receive(mqdes_wrs, ar, 100, &prio) == -1){
        wmove(chat_win, 10, 1);
        wprintw(chat_win, "FIREST READ");
    }*/
    if(mq_receive(mqdes_wrs, test_array, 150, &prio) == -1){
            wmove(chat_win, 10, 1);
            wprintw(chat_win, "FIREST READ ERR");
    }
    while(tmp != 113){     
        if(counter_chat > ws.ws_row - 8){
            refreshwin();
        }
        if(mq_receive(mqdes_rds, chat_buf, 150, &prio) == -1){
            wmove(massage_win, 3, 1); 
            wprintw(massage_win, "ERRR"); 
            sleep(3);
        }

        if(chat_buf[0] == '1' || chat_buf[0] == '2'){
            wmove(chat_win, 1, 10);
            wprintw(chat_win, "%s", &chat_buf[2]);
        }
        else if(chat_buf[0] == '3'){
            wmove(chat_win, counter_chat, 1);
            wprintw(chat_win, "%s", &chat_buf[2]);
            wmove(users_win, counter_user, 1);
            wprintw(users_win, "%s", &chat_buf[12]);
            counter_chat++;
            counter_user++;
        }
        else if(chat_buf[0] == '4'){
            wmove(chat_win, counter_chat, 1);
            wprintw(chat_win, "%s", &chat_buf[2]); 
            counter_chat++;
            counter_user--;
        }
        else{
            wmove(chat_win, counter_chat, 1);
            wprintw(chat_win, "%s", &chat_buf[2]);
            counter_chat++;
        }
        //for(int i = 1; i < counter_user; )
        for(int i = 1; i < counter_user; i++){
            if(mq_send(mqdes_wrs, &chat_buf[2], 100, 1) == -1){
                printf("ERR SEND");
            }
        } 
        chat_buf[0] = '\000';
        /*wmove(chat_win, counter_chat, 1); 
        wprintw(chat_win, "1111 %s", &chat_buf[2]); 
        wmove(users_win, counter_user, 1); 
        wprintw(users_win, "fff %d", prio); */

        wrefresh(chat_win);  
        wrefresh(users_win);  
        //sleep(1); 
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
    counter_user = 1; 

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