#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstring>
#include "ControlSimulator/RunTheSimulator.h"


int main() {
    RunTheSimulator *r = new RunTheSimulator();
    //r->parser‬‬("test.txt");
    //r->check("7/(1-5)");
    vector<string> vec = r->splitExpression("(2/(1-5) + (5 * 4))");
    vec = r->ShuntingYardAlgorithm(vec);
    Expression* e = r->createExpressionFromStrings(vec, (int)vec.size() - 1);
    return 0;
}











