//
// Created by eliran on 12/16/18.
//

#ifndef FIRSTPROJECT_SYMBOLTABLE_H
#define FIRSTPROJECT_SYMBOLTABLE_H

#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include "StoreVarValue.h"
#include <mutex>

using namespace std;

#define ONE 1


class SymbolTable {
private:
    map<string, vector<StoreVarValue<double>*>> bindValue;
    map<string, StoreVarValue<double>*> valueTable;
    map<string, StoreVarValue<string>*> destTable;
    mutex lock;

public:
    SymbolTable() {}
    ~SymbolTable();


    void addToTable(string name);

    void updateSymbolTableValue(string name, double value);

    void updateSymbolTableDest(string name, string value);

    double getSymbolTableValue(string name);

    string getSymbolTableDest(string name);

    bool existsInDestMap(string var);

    bool existsInBindValueMap(string var);

    bool existsInValueTableMap(string var);

    vector<StoreVarValue<double>*> getVariablesForUpdate(string& key);

    map<string, vector<StoreVarValue<double>*>> getBindMap();
};


#endif //FIRSTPROJECT_SYMBOLTABLE_H
