#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstring>
#include "ControlSimulator/RunTheSimulator.h"


int main() {
    RunTheSimulator *r = new RunTheSimulator();
    r->praser("test.txt");
    return 0;
}









