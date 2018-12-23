#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstring>
#include <thread>
#include "ControlSimulator/RunTheSimulator.h"
#include "ServerAndClient/DataReaderClient.h"


int main() {
    //FactoryExpression* f = new FactoryExpression(NULL);
    //Expression* e = f->create("rudder*-1");
    //cout<<e->calculate();
    bool B = false;
    string s ="127.0.0.1";
    try {
        RunTheSimulator* r = new RunTheSimulator();
        vector<string> s = r->lexer("test.txt");
        r->parser(s);
        while (true);
    } catch (const char* c) {
        cout<<c<<endl;
    }



    return 0;
}






