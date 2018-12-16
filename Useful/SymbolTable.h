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
    SymbolTable(){}

    void add(T name, K value, char table);

    void update(T name, K value, char table);

    K getSymbolValue(T name, char table);


};


#endif //FIRSTPROJECT_SYMBOLTABLE_H
