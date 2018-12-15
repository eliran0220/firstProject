#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstring>
#include "ControlSimulator/RunTheSimulator.h"


int main() {
    RunTheSimulator* r = new RunTheSimulator();
    vector<string> s = r->lexer("test.txt");
    return 0;
}











