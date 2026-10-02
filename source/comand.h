#ifndef COMAND_H
#define COMAND_H


#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <fstream>

using namespace std;

class Comand{
    private:
        string loadCSV();
        vector<array<string,3>> comandsList;
        void saveComandsInCSV();
        void loadComandsFromCSV();
    public:
        int numberOfComands;
        Comand();
        vector<string> getComandsNames();
        array<string,3> getComandData(int id);
        void addOne(string name, string discription, string comand);
        void deleteOne(int id);
        void editOne(int id,string name, string discription, string comand);
        void execute(int id);
};
#endif