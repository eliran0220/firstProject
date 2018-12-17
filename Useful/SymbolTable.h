//
// Created by eliran on 12/16/18.
//

#ifndef FIRSTPROJECT_SYMBOLTABLE_H
#define FIRSTPROJECT_SYMBOLTABLE_H

#include <map>

using namespace std;

class SymbolTable {
private:
    map<string, double> symbolTable;
    map<string, string> destTable;
public:
    SymbolTable() {}

    void addToSymbol(string name, double value);

    void addToDestTable(string name, string value);

    void updateSymbtolTable(string name, double value);

    void updateDestTable(string name, string value);

    double getValueSymbtolTable(string name);

    string getValueDestTable(string name);

    bool existsVariableValue(string var);

    bool existsVariabledest(string var);
};


#endif //FIRSTPROJECT_SYMBOLTABLE_H
