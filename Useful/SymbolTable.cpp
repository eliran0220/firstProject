//
// Created by eliran on 12/16/18.
//

#include "SymbolTable.h"


void SymbolTable::addToTable(string name) {
    StoreVarValue<string>* tempD = new StoreVarValue<string>();
    StoreVarValue<double >* tempV = new StoreVarValue<double >();
    this->valueTable[name] = tempV;
    this->destTable[name] = tempD;

}

void SymbolTable::updateSymbolTableDest(string name, string value) {
    this->destTable[name]->setInitialize(true);
    this->destTable[name]->setValue(value);
    StoreVarValue<double>* temp = this->valueTable[name];
    // עידכון של המפה של הסימולטר
    if (this->existsInSimulatorValueMap(name)) {
        this->simulatorValue[value].push_back(temp);
    } else {
        vector<StoreVarValue<double>*> vec;
        vec.push_back(temp);
        this->simulatorValue[value] = vec;
    }
}

void SymbolTable::updateSymbolTableValue(string name, double value) {
    this->valueTable[name]->setInitialize(true);
    this->valueTable[name]->setValue(value);
}

string SymbolTable::getSymbolTableDest(string name) {
    if (this->destTable[name]->checkIfInitialize()) {
        return this->destTable[name]->getValue();
    }
    throw "The variable does not Initialize";
}

double SymbolTable::getSymbolTableValue(string name) {
    if (this->valueTable[name]->checkIfInitialize()) {
        return this->valueTable[name]->getValue();
    }
    throw "The variable does not Initialize";
}

vector<StoreVarValue<double>*> SymbolTable::getVariablesForUpdate(
        string &key) {
    return this->simulatorValue[key];
}

bool SymbolTable::existsInDestMap(string var) {
    if (this->destTable.count(var) == ONE) {
        return true;
    }
    return false;
}

bool SymbolTable::existsInSimulatorValueMap(string var) {
    if (this->simulatorValue.count(var) == ONE) {
        return true;
    }
    return false;
}

bool SymbolTable::existsInValueTableMap(string var) {
    if (this->valueTable.count(var)) {
        return true;
    }
    return false;
}

SymbolTable::~SymbolTable() {
    map<string, StoreVarValue<string>*>::iterator itDe = this->destTable.begin();
    while (itDe != this->destTable.end()) {
        delete (itDe->second);
        itDe++;
    }
    map<string, StoreVarValue<double>*>::iterator itVa = this->valueTable.begin();
    while (itVa != this->valueTable.end()) {
        delete (itVa->second);
        itVa++;
    }
}


