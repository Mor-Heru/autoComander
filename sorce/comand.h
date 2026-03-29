#ifndef COMAND_H
#define COMAND_H
#include <string>
#include <vector>

using namespace std;

class comand{
private:
    static vector<comand*> Comands;
    static void save();
    static void upload();
public:
    string name;
    string description;
    string comandValue;

    static vector<comand*>& getComands() { return Comands; }
    static size_t getComandsSize() { return Comands.size(); }
    static void load() { upload(); }

    comand(string n, string c,string d="");
};

#endif