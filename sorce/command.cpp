#include "command.h"
#include <iostream>
#include <string>
#include <array>
#include <fstream>

using namespace std;

vector<command*> command::Commands;
bool command::loading = false;

void command::saveAll(){
    ofstream file("output.csv");
    for(auto cmd : Commands){
        file << cmd->name << "\t" << cmd->description << "\t" << cmd->commandValue << "\n";
    }
    cout<<"saving all"<<endl;
}
void command::upload(){
    loading = true;
    ifstream file("output.csv");
    string n,d,c,line;
    int j;
    while (getline(file, line)) {
        cout << line << endl;
        n="";
        d="";
        c="";
        j=0;
        for(int i=0;i<line.size();i++){
            if(line[i]=='\t'){
                j+=1;
                continue;
            }
            switch (j){
                case 0:
                    n+=line[i];
                    break;
                case 1:
                    d+=line[i];
                    break;
                case 2:
                    c+=line[i];
                    break;
            }
        }
        cout<<n<<endl;
        new command(n, c, d);

    }

    file.close();
    loading = false;
    cout<<"uploading"<<endl;
}
vector<array<string, 3>>  command::getCommands(){
    vector<array<string, 3>> c;
    for(int i=0; i<Commands.size(); i++){
        array<string, 3> cmd = {Commands[i]->name, Commands[i]->description, Commands[i]->commandValue};
        c.push_back(cmd);
    }
    return c;
}
command::command(string n, string c,string d){
    name=n;
    description=d;
    commandValue=c;
    Commands.push_back(this);
    if(!loading) saveAll();
}