#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include "comand.h"

using namespace std;

struct NewCommandData {
    Fl_Input* name;
    Fl_Input* description;
    Fl_Input* command;

    };

Fl_Window* windowToHide;

void loadMainWindow();

void create_callback(Fl_Widget* w, void* userdata) {
    NewCommandData* d = static_cast<NewCommandData*>(userdata);
    if (!d) return;

    string name = d->name->value();
    string description = d->description->value();
    string commandVal = d->command->value();
    comand* newComand= new comand(name,commandVal,description);
    cout<<"tezt";
    loadMainWindow();
    windowToHide->hide();
    delete d;
}

void addNewComand(Fl_Widget* w, void*) {
    windowToHide->hide();
    Fl_Window* addingComandWindow = new Fl_Window(900, 600, "Add comand");

    Fl_Input *inputName = new Fl_Input(300, 80, 200, 30, "comand name");
    Fl_Input *inputDescription = new Fl_Input(300, 120, 200, 30, "description");
    Fl_Input *inputComandToExecute = new Fl_Input(300, 160, 200, 30, "comand to execute");
    Fl_Button* creatingbutton = new Fl_Button(700, 500, 100, 40, "Create");

    NewCommandData* data=new NewCommandData{inputName,inputDescription,inputComandToExecute};
    windowToHide=addingComandWindow;

    creatingbutton->callback(create_callback,data);
    addingComandWindow->end();
    addingComandWindow->show();
}

void loadMainWindow(){
    Fl_Window* mainWindow = new Fl_Window(900, 600, "autoComander");
    Fl_Button* addingComandbutton = new Fl_Button(700, 500, 100, 40, "Add comand");
    windowToHide=mainWindow;
    addingComandbutton->callback(addNewComand);

    mainWindow->end();
    mainWindow->show();
}

int main() {
    loadMainWindow();
    return Fl::run();
}