#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Scroll.H>
#include "command.h"
#include <array>
#include <vector>
#include <cstdlib>

using namespace std;

struct NewCommandData {
    Fl_Input* name;
    Fl_Input* description;
    Fl_Input* command;
};

struct CommandButtonData {
    string commandValue;
};

Fl_Window* editingCommandWindow;
Fl_Window* mainWindow;
Fl_Scroll* scrollArea;

void loadMainWindow();
void create_callback(Fl_Widget* w, void* userdata);
void addNewCommand(Fl_Widget* w, void*);
void executeCommand_callback(Fl_Widget* w, void* userdata);

void executeCommand_callback(Fl_Widget* w, void* userdata) {
    CommandButtonData* data = static_cast<CommandButtonData*>(userdata);
    if (!data) return;
    
    string cmd = data->commandValue;
    cout << "Executing: " << cmd << endl;
    system(cmd.c_str());
}

void create_callback(Fl_Widget* w, void* userdata) {
    NewCommandData* d = static_cast<NewCommandData*>(userdata);
    if (!d) return;

    string name = d->name->value();
    string description = d->description->value();
    string commandVal = d->command->value();
    if (name.empty() || commandVal.empty()) {
        cout<<"error"<<endl;
        return;
    }
    command* newCommand = new command(name, commandVal, description);
    loadMainWindow();
    editingCommandWindow->hide();
    delete editingCommandWindow;
    delete d;
}

void addNewCommand(Fl_Widget* w, void*) {
    mainWindow->hide();
    editingCommandWindow = new Fl_Window(900, 600, "Edit command");
    Fl_Input* inputName = new Fl_Input(300, 80, 200, 30, "Command name");
    Fl_Input* inputDescription = new Fl_Input(300, 120, 200, 30, "Description");
    Fl_Input* inputCommandToExecute = new Fl_Input(300, 160, 200, 30, "Command to execute");
    Fl_Button* createButton = new Fl_Button(700, 500, 100, 40, "Create");

    NewCommandData* data = new NewCommandData{inputName, inputDescription, inputCommandToExecute};

    createButton->callback(create_callback, data);
    editingCommandWindow->end();
    editingCommandWindow->show();
}

void loadMainWindow() {
    if (mainWindow) {
        delete mainWindow;
    }
    
    vector<array<string, 3>> list = command::getCommands();
    
    mainWindow = new Fl_Window(900, 600, "autoCommander");
    
    scrollArea = new Fl_Scroll(10, 10, 880, 480);
    scrollArea->type(Fl_Scroll::VERTICAL);
    scrollArea->begin();
    string output;
    for(size_t i = 0; i < list.size(); i++){
        int yPos = 10 + i * 60;
        // Label z nazwą komendy
        Fl_Box* nameBox = new Fl_Box(20, yPos, 300, 50);
        nameBox->copy_label(list[i][0].c_str());
        nameBox->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
        
        // Przycisk do wykonania komendy
        Fl_Button* executeButton = new Fl_Button(350, yPos, 100, 50, "Execute");
        CommandButtonData* btnData = new CommandButtonData{list[i][2]};
        executeButton->callback(executeCommand_callback, btnData);
    }
    
    scrollArea->end();
    
    Fl_Button* addCommandButton = new Fl_Button(700, 520, 100, 40, "Add command");
    addCommandButton->callback(addNewCommand);

    mainWindow->end();
    mainWindow->show();
}

int main() {
    command::load();
    loadMainWindow();
    return Fl::run();
}