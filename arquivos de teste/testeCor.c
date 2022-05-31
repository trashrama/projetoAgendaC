
#include <ncurses.h>
#include <stdlib.h>

int main(int argc, char const *argv[]){
    

    initscr();

    WINDOW * win = newwin(10, 20, 10, 10);
    refresh();

    box(win, 0, 0);
    wrefresh(win);

    getch();

    endwin();

    return 0;
}
