#include <iostream>
#include "ControlSimulator/RunTheSimulator.h"

int main(int argc, char *argv[]) {
    RunTheSimulator*  r =  new RunTheSimulator();
    try {
        vector<string> s = r->lexer(argv[1]);
        r->parser(s);
    } catch (const char *exception) {
        cout << exception<<endl;
    } catch (...) {}
    delete (r);
    return 0;
}






