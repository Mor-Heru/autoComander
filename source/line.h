#ifndef LINE_H
#define LINE_H
#include <string>
#include <ncurses.h>
#include "comand.h"

using namespace std;

class Line{
    private:
    void createLine(bool selected,int selectedButton);
    int id;
    string name;
    string discription;
    string comand;
    Comand* ComandsOperator = nullptr;
    public:
    Line(int i,string n,string d, string c, Comand& co);
    void setSelected(bool selected,int selectedButton);
    void run();
    void edit();
    void del();
};
#endif