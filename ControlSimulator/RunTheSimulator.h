//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_RUNTHESIMULATOR_H
#define FIRSTPROJECT_RUNTHESIMULATOR_H

#define WHILE_LOOP "while"
#define FOR_LOOP "for"
#define IF "if"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>

using namespace std;

enum {
    EQUAL
};

class RunTheSimulator {
public:
    RunTheSimulator() {}

    void praser(string fileName);

    vector<string> splitCommand(const string &givenLine);

    vector<string> lexer(fstream &file);

    vector<string> conditionCommand(vector<string> command, fstream &file,
                            const string &givenLine);

    bool checkIfLineCondition(const string &givenLine);
};


#endif //FIRSTPROJECT_RUNTHESIMULATOR_H
