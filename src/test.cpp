#include <iostream>
#include "ncurses.h"

int main()
{
    initscr();
    addch('h');
    addch('h');
    addch('h');
    addch('h');
    getch();
    endwin();

    return 0;
}
