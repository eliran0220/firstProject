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
    r->check("2/(1-5)");
    return 0;
}









