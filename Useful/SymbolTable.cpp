//
// Created by eliran on 12/16/18.
//

#include "SymbolTable.h"


void SymbolTable::addToSymbol(string name, double value) {
    this->symbolTable.insert(pair<string,double>(name,value));
}

void SymbolTable::addToDestTable(string name, string value) {
    this->destTable.insert(pair<string,string>(name,value));
}

void SymbolTable::updateSymbtolTable(string name, double value) {
    this->symbolTable.at(name) = value;
}

void SymbolTable::updateDestTable(string name, string value) {
    this->destTable.at(name) = value;
}

double SymbolTable::getValueSymbtolTable(string name) {
    return this->symbolTable.at(name);
}

string SymbolTable::getValueDestTable(string name) {
    return this->destTable.at(name);
}




