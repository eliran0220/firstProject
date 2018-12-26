#include <iostream>
#include "ControlSimulator/RunTheSimulator.h"

int main(int argc, char *argv[]) {
    RunTheSimulator*  runTheSimulator =  new RunTheSimulator();
    try {
        vector<string> split = runTheSimulator->lexer(argv[1]);
        runTheSimulator->parser(split);
    } catch (const char *exception) {
        cout << exception<<endl;
    } catch (...) {}
    delete (runTheSimulator);
    return 0;
}






