#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstring>
#include <thread>
#include "ControlSimulator/RunTheSimulator.h"
#include "ServerAndClient/DataReaderClient.h"

static void run(int port);
static int createSocket(int port);

int main() {
    FactoryExpression* f = new FactoryExpression(NULL);
    Expression* e = f->create("(0-1)*(0-1)");
    cout<<e->calculate();
    /*
    try {
        RunTheSimulator* r = new RunTheSimulator();
        vector<string> s = r->lexer("test.txt");
        r->parser(s);
    } catch (const char* c) {
        cout<<c<<endl;
    }
     */
    return 0;
}






