#include "terminal.h"
#include "comand.h"
#include "line.h"

#include <vector>
#include <array>
#include <string>
#include <ncurses.h>

using namespace std;

Comand ComandsOperator = Comand();

vector<Line> lines;

static void RebuildLines()
{
    lines.clear();

    for (int i = 0; i < ComandsOperator.numberOfComands; ++i)
    {
        array<string, 3> data = ComandsOperator.getComandData(i);
        lines.emplace_back(i, data[0], data[1], data[2], ComandsOperator);
    }
}


// ============================================================
// HEADER
// ============================================================

void Terminal::CreateHeader(bool selectedAdd)
{
    mvprintw(2, 80, "%s", "WELCOME IN AUTOCOMMANDER!");

    mvhline(4, 2, ACS_HLINE, 186);

    // ADD NEW COMMAND
    if (selectedAdd)
        attron(COLOR_PAIR(2));

    mvprintw(2, 150, "[ ADD NEW COMMAND ]");

    if (selectedAdd)
        attroff(COLOR_PAIR(2));
}


// ============================================================
// ASIDE
// ============================================================

void Terminal::CreateAside()
{
    mvvline(5, 143, ACS_VLINE, 40);
}


// ============================================================
// ADD NEW COMMAND WINDOW
// ============================================================

void Terminal::CreateNewCommandWindow()
{
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

    mvwprintw(win, 2, 40, "ADD NEW COMMAND");
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

                ComandsOperator.addOne(
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


// ============================================================
// TERMINAL
// ============================================================

Terminal::Terminal()
{
    initscr();

    cbreak();
    noecho();

    keypad(stdscr, TRUE);

    start_color();

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_BLACK, COLOR_CYAN);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);

    box(stdscr, 0, 0);

    int height;
    int width;

    getmaxyx(stdscr, height, width);

    RebuildLines();

    // --------------------------------------------------------
    // SELECTION
    // --------------------------------------------------------

    int selectedLine = 0;

    // 0 = RUN
    // 1 = EDIT
    int selectedButton = 0;

    // Whether ADD NEW COMMAND is selected.
    bool selectedAdd = false;

    // --------------------------------------------------------
    // MAIN LOOP
    // --------------------------------------------------------

    while (true)
    {
        RefreshScreen(selectedLine, selectedButton, selectedAdd);

        int key = getch();

        // ====================================================
        // UP
        // ====================================================

        if (key == KEY_UP)
        {
            if (selectedAdd)
            {
                // ADD is already selected.
            }
            else if (selectedLine == 0)
            {
                // Move from the first command to ADD.
                selectedAdd = true;
            }
            else
            {
                selectedLine--;
            }
        }

        // ====================================================
        // DOWN
        // ====================================================

        else if (key == KEY_DOWN)
        {
            if (selectedAdd)
            {
                // Move from ADD to the first command.
                selectedAdd = false;
                selectedLine = 0;
            }
            else if (
                selectedLine <
                static_cast<int>(lines.size()) - 1
            )
            {
                selectedLine++;
            }
        }

        // ====================================================
        // LEFT
        // ====================================================

        else if (key == KEY_LEFT)
        {
            if (!selectedAdd)
            {
                if (selectedButton > 0)
                    selectedButton--;
            }
        }

        // ====================================================
        // RIGHT
        // ====================================================

        else if (key == KEY_RIGHT)
        {
            if (!selectedAdd)
            {
                if (selectedButton < 2)
                    selectedButton++;
            }
        }

        // ====================================================
        // ENTER
        // ====================================================

        else if (key == '\n' || key == KEY_ENTER)
        {
            // -----------------------------------------------
            // ADD NEW COMMAND
            // -----------------------------------------------

            if (selectedAdd)
            {
                CreateNewCommandWindow();
                RebuildLines();

                // Return to the command list.
                selectedAdd = false;

                if (!lines.empty())
                {
                    selectedLine =
                        static_cast<int>(lines.size()) - 1;
                }
                else
                {
                    selectedLine = 0;
                }
            }

            // -----------------------------------------------
            // RUN / EDIT
            // -----------------------------------------------

            else if (
                selectedLine >= 0 &&
                selectedLine < static_cast<int>(lines.size())
            )
            {
                if (selectedButton == 0)
                {
                    endwin();
                    lines[selectedLine].run();
                    break;
                }
                else if (selectedButton == 1)
                {
                    lines[selectedLine].edit();
                    RebuildLines();
                }
                else if (selectedButton == 2)
                {
                    lines[selectedLine].del();
                    RebuildLines();

                    if (selectedLine >= static_cast<int>(lines.size()))
                        selectedLine = static_cast<int>(lines.size()) - 1;
                    if (selectedLine < 0)
                        selectedLine = 0;
                }
            }
        }

        // ====================================================
        // A = QUICK ACCESS TO ADD
        // ====================================================

        else if (key == 'a' || key == 'A')
        {
            selectedAdd = true;
        }

        // ====================================================
        // Q = QUIT
        // ====================================================

        else if (key == 'q' || key == 'Q')
        {
            break;
        }
    }
}


// ============================================================
// DESTRUCTOR
// ============================================================

Terminal::~Terminal()
{
    endwin();
}

void Terminal::RefreshScreen(int selectedLine, int selectedButton, bool selectedAdd)
{
    clear();
    box(stdscr, 0, 0);

    CreateHeader(selectedAdd);
    CreateAside();

    for (int i = 0; i < static_cast<int>(lines.size()); ++i)
    {
        bool selected = !selectedAdd && i == selectedLine;
        lines[i].setSelected(selected, selectedButton);
    }

    refresh();
}