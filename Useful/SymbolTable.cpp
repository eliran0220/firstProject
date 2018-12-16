//
// Created by eliran on 12/16/18.
//

#include "SymbolTable.h"


template<typename T, typename K>
void SymbolTable<T, K>::add(T name, K value, char table) {
    if (table == 's')
        this->symbolTable.insert(pair<string, double>(name, value));
    this->destTable.insert(pair<string, string>(name, value));
}

template<typename T, typename K>
void SymbolTable<T, K>::update(T name, K value, char table) {
    if (table == 's')
        this->symbolTable.at(name) = value;
    this->destTable.at(name) = value;
}

template<typename T, typename K>
K SymbolTable<T, K>::getSymbolValue(T name, char table) {
    if (table == 's')
        return this->symbolTable.at(name);
    return this->destTable.at(name);
}

