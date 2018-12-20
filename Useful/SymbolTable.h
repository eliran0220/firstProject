//
// Created by eliran on 12/16/18.
//

#ifndef FIRSTPROJECT_SYMBOLTABLE_H
#define FIRSTPROJECT_SYMBOLTABLE_H

#include <map>
#include <algorithm>
#include "StoreVarValue.h"

using namespace std;

#define ONE 1


class SymbolTable {
private:
    map<string, StoreVarValue<double>*> valueTable;
    map<string, StoreVarValue<string>*> destTable;
public:
    SymbolTable() {}
    ~SymbolTable();


    void addToTable(string name);

    void updateSymbolTableValue(string name, double value);

    void updateSymbolTableDest(string name, string value);

    double getSymbolTableValue(string name);

    string getSymbolTableDest(string name);

    bool existsVariable(string var);
};


#endif //FIRSTPROJECT_SYMBOLTABLE_H
