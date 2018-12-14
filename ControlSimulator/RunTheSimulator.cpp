//
// Created by afik on 12/13/18.
//



#include "RunTheSimulator.h"

void RunTheSimulator::praser(string fileName) {
    fstream file(fileName);
    if (!file) {
        cout << "file does not exists";
        return;
    }
    vector<string> command = lexer(file);
    while (!command.empty()) {
        command = lexer(file);
    }
    file.close();
}

vector<string> RunTheSimulator::lexer(fstream &file) {
    vector<string> command;
    string line;
    bool check;
    if (!file.eof()) {
        getline(file, line);
        /*
         * Prototype algorithem for conditions:
         * check if a line contains a condition
         * if we see a line which contains "if,while,for" we do the split
         * command function, and repeat the algorithem untill we see }
         * than, we add } to the vector.
         */
        check = checkIfLineCondition(line);
        if (check) {

        }
        command = splitCommand(line);

    }
    return command;
}

vector<string> RunTheSimulator::splitCommand(const string &givenLine) {
    vector<string> vec;
    stringstream ss(givenLine);
    string item;
    getline(ss, item, ' ');
    while (getline(ss, item, ' ')) {
        if (strcmp(item.c_str(), "") == EQUAL ||
            strcmp(item.c_str(), "=") == EQUAL) {
            continue;
        }
        item.erase(std::remove(item.begin(), item.end(), '"'), item.end());
        vec.push_back(item);
    }
    return vec;
}

string RunTheSimulator::conditionCommand(const string &givenLine) {

}

bool RunTheSimulator::checkIfLineCondition(const string &givenLine) {
    return givenLine.find(WHILE_LOOP) || givenLine.find(FOR_LOOP)
           || givenLine.find(IF);
}

