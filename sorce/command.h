#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <vector>
#include <array>

using namespace std;

class command{
private:
    static vector<command*> Commands;
    static bool loading;
    static void saveAll();
    static void upload();
public:
    string name;
    string description;
    string commandValue;

    static vector<array<string, 3>>  getCommands();
    static void load() { upload(); }

    command(string n, string c,string d="");
};

#endif