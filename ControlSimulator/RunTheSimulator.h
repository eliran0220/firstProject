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

using namespace std;

enum {EQUAL};

class RunTheSimulator {
    vector<Expression*> expressions;

public:
    RunTheSimulator() {}

    void parser(string fileName);

    vector<string> splitCommand(const string &givenLine);

    vector<string> lexer(fstream &file);

    vector<string> ReadConditionBLock(fstream &file, const string &firstLineBlock);

    vector<string> ShuntingYardAlgorithm(vector<string> strings);

    vector<string> splitExpression(string stringExpression);

    Expression* createExpressionFromStrings(vector<string> strings, int position);
};


#endif //FIRSTPROJECT_RUNTHESIMULATOR_H
