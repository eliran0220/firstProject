#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

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
    map<string, vector<string>> bindValue;
    map<string, double > valueTable;
    map<string, string> destTable;

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

    vector<string> getVariablesForUpdate(string &key);

    map<string, vector<string>> getBindMap();
};


#endif
