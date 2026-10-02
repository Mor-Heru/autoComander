#include "line.h"
#include <string>
#include <ncurses.h>
#include "comand.h"


Line::Line(int i, string n, string d, string c, Comand& co)
{
    this->id = i;
    this->name = n;
    this->discription = d;
    this->comand = c;
    this->ComandsOperator = &co;
}


// ============================================================
// RYSOWANIE LINII
// ============================================================

void Line::createLine(bool selected=false,int selectedButton=0)
{
    if (selected)
        attron(COLOR_PAIR(2));

    mvprintw((id * 3) + 6, 2, "%s", name.c_str());

    if (selected)
        attroff(COLOR_PAIR(2));

    mvhline(
        (id * 3) + 7,
        2,
        ACS_HLINE,
        140
    );
}


// ============================================================
// ZAZNACZENIE
// ============================================================

void Line::setSelected(bool selected, int selectedButton)
{
    createLine(selected,selectedButton);
    // ========================================================
    // RUN
    // ========================================================

    if (selected && selectedButton == 0)
        attron(COLOR_PAIR(2));

    mvprintw((id * 3) + 6, 100, "[RUN]");

    if (selected && selectedButton == 0)
        attroff(COLOR_PAIR(2));

    // ========================================================
    // EDIT
    // ========================================================

    if (selected && selectedButton == 1)
        attron(COLOR_PAIR(2));

    mvprintw((id * 3) + 6, 115, "[EDIT]");

    if (selected && selectedButton == 1)
        attroff(COLOR_PAIR(2));

    // ========================================================
    // DELETE
    // ========================================================

    if (selected && selectedButton == 2)
        attron(COLOR_PAIR(2));

    mvprintw((id * 3) + 6, 130, "[DELETE]");

    if (selected && selectedButton == 2)
        attroff(COLOR_PAIR(2));
}


// ============================================================
// RUN
// ============================================================

void Line::run()
{
    if (ComandsOperator != nullptr)
        ComandsOperator->execute(id);
}

void Line::del(){
    if (ComandsOperator != nullptr)
        ComandsOperator->deleteOne(id);
}

void Line::edit(){
    int height, width;

    getmaxyx(stdscr, height, width);

    int winHeight = 30;
    int winWidth = 90;

    int startY = (height - winHeight) / 2;
    int startX = (width - winWidth) / 2;

    WINDOW* win = newwin(
        winHeight,
        winWidth,
        startY,
        startX
    );

    keypad(win, TRUE);

    char name[50] = "";
    char description[100] = "";
    char command[100] = "";

    werase(win);
    box(win, 0, 0);

    mvwprintw(win, 2, 40, "EDIT COMMAND");
    mvwhline(win, 4, 2, ACS_HLINE, 86);

    mvwprintw(win, 6, 8, "Name:");
    mvwprintw(win, 10, 8, "Description:");
    mvwprintw(win, 14, 8, "Command:");

    echo();

    mvwprintw(win, 6, 20, "[");
    wmove(win, 6, 21);
    wgetnstr(win, name, 48);

    mvwprintw(win, 10, 20, "[");
    wmove(win, 10, 21);
    wgetnstr(win, description, 48);

    mvwprintw(win, 14, 20, "[");
    wmove(win, 14, 21);
    wgetnstr(win, command, 48);

    noecho();

    int selected = 0;

    while (true)
    {
        werase(win);
        box(win, 0, 0);

        mvwprintw(win, 2, 40, "ADD NEW COMMAND");
        mvwhline(win, 4, 2, ACS_HLINE, 86);

        mvwprintw(win, 6, 8, "Name:");
        mvwprintw(win, 6, 20, "[%s]", name);

        mvwprintw(win, 10, 8, "Description:");
        mvwprintw(win, 10, 20, "[%s]", description);

        mvwprintw(win, 14, 8, "Command:");
        mvwprintw(win, 14, 20, "[%s]", command);

        // ADD
        if (selected == 0)
            wattron(win, COLOR_PAIR(2));

        mvwprintw(win, 26, 35, "[ADD]");

        if (selected == 0)
            wattroff(win, COLOR_PAIR(2));

        // CANCEL
        if (selected == 1)
            wattron(win, COLOR_PAIR(2));

        mvwprintw(win, 26, 45, "[CANCEL]");

        if (selected == 1)
            wattroff(win, COLOR_PAIR(2));

        wrefresh(win);

        int key = wgetch(win);

        if (key == KEY_LEFT)
        {
            selected = 0;
        }
        else if (key == KEY_RIGHT)
        {
            selected = 1;
        }
        else if (key == '\n' || key == KEY_ENTER)
        {
            if (selected == 0)
            {
                string sName(name);
                string sDescription(description);
                string sCommand(command);

                ComandsOperator->editOne(
                    id,
                    sName,
                    sDescription,
                    sCommand
                );

                break;
            }
            else
            {
                break;
            }
        }
    }

    delwin(win);

    touchwin(stdscr);
    refresh();

}