//
// Created by afik on 12/13/18.
//



#include "RunTheSimulator.h"

void RunTheSimulator::praser(string fileName) {
    fstream file(fileName);
    if (!file) {
        cout<< "file does not exists";
        return;
    }
    vector<string> command = lexer(file);
    while (!command.empty()) {
        command =  lexer(file);
    }
    file.close();
}

vector<string> RunTheSimulator::lexer(fstream& file) {
    vector<string> command;
    string line;
    if (!file.eof()) {
        getline(file, line);
        command = splitCommand(line);
    }
    return command;
}

vector<string> RunTheSimulator::splitCommand(const string &givenLine){
    vector<string> vec;
    stringstream ss(givenLine);
    string item;
    getline(ss, item, ' ');
    while (getline(ss, item, ' ')){
        if (strcmp(item.c_str(),"") == EQUAL || strcmp(item.c_str(),"=") == EQUAL) {
            continue;
        }
        item.erase(std::remove(item.begin(), item.end(), '\\'), item.end());
        vec.push_back(item);
    }
    return vec;
}