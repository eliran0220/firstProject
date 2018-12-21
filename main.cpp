#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstring>
#include "ControlSimulator/RunTheSimulator.h"
#include "ServerAndClient/DataReaderServer.h"

int main() {
    // ליצור את כל המחלקות של הקומאנדים
    // ליצור מחלקה שמחזירה את כל המשתנים var
    // במחלקה יהיה מפה בין מחרוזת לקומאנד
    /*
    try {
        FactoryExpression *f = new FactoryExpression(NULL);
        Expression *e = f->create("5+-(7+8)");
        cout<<e->calculate()<<endl;
    } catch (const char* c) {
        cout<<c<<endl;
    }
     */


    try {
        RunTheSimulator* r = new RunTheSimulator();
        vector<string> s = r->lexer("test.txt");
        r->parser(s);
    } catch (const char* c) {
        cout<<c<<endl;
    }


    //FactoryExpression* factoryExpression = new FactoryExpression(NULL);
    int x = 5;
    //Expression* e = factoryExpression->create("(5/2) +5");
    //r->parser(s);
    //delete (r);

    return 0;
}











