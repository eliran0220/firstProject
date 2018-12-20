#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstring>
#include "ControlSimulator/RunTheSimulator.h"

int main() {
    // ליצור את כל המחלקות של הקומאנדים
    // ליצור מחלקה שמחזירה את כל המשתנים var
    // במחלקה יהיה מפה בין מחרוזת לקומאנד


    try {
        RunTheSimulator* r = new RunTheSimulator();
        vector<string> s = r->lexer("test.txt");
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











