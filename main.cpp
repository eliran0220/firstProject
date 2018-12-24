#include <iostream>
#include "ControlSimulator/RunTheSimulator.h"

int main() {
    RunTheSimulator* r = new RunTheSimulator();
    try {
        vector<string> s = r->lexer("test.txt");
        r->parser(s);
    } catch (const char *exception) {
        cout << exception<<endl;
    } catch (...) {}
    delete (r);
    return 0;
}






