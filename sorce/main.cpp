#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Table.H>
#include <FL/Fl_Table_Row.H>
#include "comand.h"

using namespace std;

struct NewCommandData {
    Fl_Input* name;
    Fl_Input* description;
    Fl_Input* command;

    };

void create_callback(Fl_Widget* w, void* userdata) {
    NewCommandData* d = static_cast<NewCommandData*>(userdata);
    if (!d) return;

    string name = d->name->value();
    string description = d->description->value();
    string commandVal = d->command->value();

    comand* newComand= new comand(name,commandVal,description);

    delete d;
}

void addNewComand(Fl_Widget* w, void*) {
    Fl_Window* addingComandWindow = new Fl_Window(900, 600, "Add comand");

    Fl_Input *inputName = new Fl_Input(300, 80, 200, 30, "comand name");
    Fl_Input *inputDescription = new Fl_Input(300, 120, 200, 30, "description");
    Fl_Input *inputComandToExecute = new Fl_Input(300, 160, 200, 30, "comand to execute");
    Fl_Button* creatingbutton = new Fl_Button(700, 500, 100, 40, "Create");

    NewCommandData* data=new NewCommandData{inputName,inputDescription,inputComandToExecute};

    creatingbutton->callback(create_callback,data);
    addingComandWindow->end();
    addingComandWindow->show();
}

int main() {
    Fl_Window* mainWindow = new Fl_Window(900, 600, "autoComander");
    Fl_Button* addingComandbutton = new Fl_Button(700, 500, 100, 40, "Add comand");
    addingComandbutton->callback(addNewComand);

    mainWindow->end();
    mainWindow->show();
    return Fl::run();
}