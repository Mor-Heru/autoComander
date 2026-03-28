#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>

using namespace std;

void callback(Fl_Widget* w, void*) {
    w->label("Kliknięto!");
}

int main() {
    Fl_Window* window = new Fl_Window(300, 200, "Pierwsze FLTK");
    Fl_Button* button = new Fl_Button(100, 80, 100, 40, "Kliknij mnie");
    button->callback(callback);

    window->end();
    window->show();
    return Fl::run();
}