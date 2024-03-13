#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h> 
extern WINDOW * stdscr;
int win_size_x, win_size_y;

void sig_winch(int signo){
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col); 
    win_size_y = size.ws_row;
    win_size_x = size.ws_col;
}

int main(){
    WINDOW *wnd;
    WINDOW *subwnd;

    initscr();
    signal(SIGWINCH, sig_winch);
    cbreak();
    curs_set(0); 
    refresh();


    wnd = newwin(20, 50, 2, 4);
    box(wnd, '|', '-');
    subwnd = derwin(wnd, 10, 25, 3, 3);
    box(subwnd, 'I', '_');
    wmove(subwnd, 2, 2);
    wprintw(subwnd, "Hello");
    wrefresh(wnd); 
    move(22, 5);
    printw("Press any key to continue...");

    delwin(subwnd);
    delwin(wnd); 
    getch();
    endwin();
    return 0; 
}
