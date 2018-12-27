#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <algorithm>
#include <string>
#include <vector>
#include "StoreVarValue.h"
#include <mutex>
#include <queue>

using namespace std;

#define ONE 1

using namespace std;

class SymbolTable {
private:
    map<string, vector<string>> bindValue;
    map<string, StoreVarValue<double> *> valueTable;
    map<string, StoreVarValue<string> *> destTable;
    mutex mtx;
    queue<map<string, double>> needToUpdate;

public:
    SymbolTable() {}

    ~SymbolTable();


    void addToTable(string name);

    void updateSymbolTableValue(string name, double value);

    void updateSymbolTableDest(string name, string value);

    double getSymbolTableValue(string name);

    string getSymbolTableDest(string name);

    void varsToUpdate(string name, double value);

    bool existsInBindValueMap(string var);

    bool existsInValueTableMap(string var);

    vector<string> getVariablesForUpdate(string &key);

    queue<map<string, double>>* getQueueToUpdate();
};


#endif
