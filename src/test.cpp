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
    // g++ -std=c++17 src/main.cpp src/ProcessParser.cpp src/util.cpp -o main -lncurses
    return 0;
}
