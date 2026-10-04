#include "comand.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <filesystem>

using namespace std;

namespace {
    filesystem::path commandsCsvPath() {
        return filesystem::read_symlink("/proc/self/exe").parent_path()
            / "data/comands.csv";
    }
}

    string Comand::loadCSV(){
        string csv,l;

        ifstream csvWithComands(commandsCsvPath());

        // Use a while loop together with the getline() function to read the file line by line
        while (getline (csvWithComands, l)) {
        // Output the text from the file
        csv+=l+"\n";
        }
        csvWithComands.close(); 
        return csv;
    }

    void Comand::saveComandsInCSV(){
        ofstream csvWithSavedComands(commandsCsvPath());// Open the file.

        string comand="";

        for(int i = 0; i < comandsList.size(); i++){
            for(int j = 0; j < 3; j++){
                comand += comandsList[i][j] + "\t";
            }
            csvWithSavedComands << comand+"\n";
            comand = "";
        }

        csvWithSavedComands.close();
    }

    void Comand::loadComandsFromCSV(){
        ifstream csvWithSavedComands(commandsCsvPath());// Open the file.
            
        array <string,3> readingComand;// Stores the name, description, and command currently being read.
        int whichPart; // Tracks which field is currently being read.

        string lineWithComand;
        while(getline(csvWithSavedComands,lineWithComand)){// Read the file.

            whichPart=0;// Reset the field index.
            readingComand={"","",""};

            for(int i=0;i<lineWithComand.size();i++){

                if(lineWithComand[i]=='\t'){// Check whether the character is a tab.
                    whichPart++;
                    continue;
                }
                    
                readingComand[whichPart]+=lineWithComand[i];// Append the character to the current field.
            }

            comandsList.push_back(readingComand);
        }
        csvWithSavedComands.close();
        
        numberOfComands=comandsList.size();
    }
    
    Comand::Comand(){
        loadComandsFromCSV();
    }

    vector<string> Comand::getComandsNames(){
        vector<string> names;
        for (int i=0;i<comandsList.size();i++){
            names.push_back(comandsList[i][0]);
            
        }
        return names;
    }

       void Comand::addOne(string name, string discription, string comand){
        array<string,3> line={name,discription,comand};
        comandsList.push_back(line);
        string lineCSV="";
        for(int i=0;i<3;i++){
            lineCSV+=line[i]+"\t";
        }

        string csv=loadCSV();

        ofstream csvToSavedComands(commandsCsvPath());// Open the file.
        csvToSavedComands << csv+lineCSV;
        csvToSavedComands.close();
        numberOfComands++;
    }

    array<string,3> Comand::getComandData(int id){
        return comandsList[id];
    }

    void Comand::deleteOne(int id){
        comandsList.erase(comandsList.begin()+id);
        saveComandsInCSV();
        numberOfComands--;
    }

    void Comand::editOne(int id,string name, string discription, string comand){
        if(name==""){
            name=comandsList[id][0];
        }
        if(discription==""){
            discription=comandsList[id][1];
        }
        if(comand==""){
            comand=comandsList[id][2];
        }        
        comandsList[id]={name,discription,comand};
        saveComandsInCSV();
    }

    void Comand::execute(int id){
        system("clear");
        system(comandsList[id][2].c_str());
    }