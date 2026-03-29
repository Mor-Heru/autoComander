#include "comand.h"
#include <iostream>
#include <string>

using namespace std;

vector<comand*> comand::Comands;

void comand::save(){
    cout<<"saving"<<endl;
}
void comand::upload(){
    cout<<"uploading"<<endl;
}
comand::comand(string n, string c,string d){
    name=n;
    description=d;
    comandValue=c;
    Comands.push_back(this);
}