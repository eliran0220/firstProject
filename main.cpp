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
    RunTheSimulator* r = new RunTheSimulator();
    vector<string> s = r->lexer("test.txt");
    r->parser(s);
    delete (r);
    return 0;
}











