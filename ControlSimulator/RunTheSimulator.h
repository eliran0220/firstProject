//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_RUNTHESIMULATOR_H
#define FIRSTPROJECT_RUNTHESIMULATOR_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <algorithm>

using namespace std;

enum{EQUAL};

class RunTheSimulator {
public:
    RunTheSimulator(){}
    void praser(string fileName);
    vector<string> splitCommand(const string &givenLine);
    vector<string> lexer(fstream& file)
};


#endif //FIRSTPROJECT_RUNTHESIMULATOR_H
