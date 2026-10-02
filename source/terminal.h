#ifndef TERMINAL_H
#define TERMINAL_H

#include <ncurses.h>

using namespace std;

class Terminal {
private:
    int selected = 0;
    void CreateHeader(bool selectedAdd);
    void CreateAside();
    void CreateNewCommandWindow();
public:
    Terminal();
    ~Terminal();
    void RefreshScreen(int selectedLine, int selectedButton, bool selectedAdd);
};

#endif