#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include "StoreVarValue.h"
#include <mutex>

#define ONE 1

using namespace std;

class SymbolTable {
private:
    map<string, vector<StoreVarValue<double> *>> bindValue;
    map<string, StoreVarValue<double> *> valueTable;
    map<string, StoreVarValue<string> *> destTable;

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

    vector<StoreVarValue<double> *> getVariablesForUpdate(string &key);

    map<string, vector<StoreVarValue<double> *>> getBindMap();
};


#endif
