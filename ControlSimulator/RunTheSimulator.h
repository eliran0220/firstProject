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
#include "../Expressions/Expression.h"
#include "../Useful/CollectionCommands.h"


using namespace std;

enum {EQUAL};

class RunTheSimulator {
    CollectionCommands* collectionCommands;


public:
    RunTheSimulator();
    ~RunTheSimulator();

    void parser(vector<string> commands);

    vector<string> splitCommand(const string &givenLine);

    vector<string> lexer(string fileName);

    //vector<string> ReadConditionBLock(fstream &file, const string &firstLineBlock);

};


#endif //FIRSTPROJECT_RUNTHESIMULATOR_H
