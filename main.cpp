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
    //RunTheSimulator* r = new RunTheSimulator();
    //vector<string> s = r->lexer("test.txt");
    //FactoryExpression* factoryExpression = new FactoryExpression(NULL);
    //Expression* e = factoryExpression->create("(5/2) +5");
    //r->parser(s);
    //delete (r);
    FactoryExpression f = FactoryExpression(NULL);
    cout<< f.create("9 - 2*3")->calculate();
    return 0;
}











