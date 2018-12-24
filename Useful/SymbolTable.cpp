//
// Created by eliran on 12/16/18.
//

#include "SymbolTable.h"

/**
 * Function name: addToTable
 * The input: string
 * The output: none
 * The function operation: The function adds the given string to the maps.
 * The string represents the variable which will be added
 * @param name given string
 */
void SymbolTable::addToTable(string name) {
    StoreVarValue<string> *tempD = new StoreVarValue<string>();
    StoreVarValue<double> *tempV = new StoreVarValue<double>();
    this->valueTable[name] = tempV;
    this->destTable[name] = tempD;

}

/**
 * Function name: updateSymbtolTableDest
 * The input: string, string
 * The output: none
 * The function operation: The function updates the table dest with the given string (name) to the
 * given string (value).
 * We initialize the name var in the dest, value, to true , so we would know it exists,
 * and then we set the value in the dest table.
 * @param name string
 * @param value string
 */
void SymbolTable::updateSymbolTableDest(string name, string value) {
    mutex mtx;
    unique_lock<mutex> lock(mtx);
    this->destTable[name]->setInitialize(true);
    this->valueTable[name]->setInitialize(true);
    this->destTable[name]->setValue(value);
    StoreVarValue<double> *temp = this->valueTable[name];
    // עידכון של המפה של הסימולטר
    if (this->existsInBindValueMap(value)) {
        this->bindValue[value].push_back(temp);
    } else {
        vector<StoreVarValue<double> *> vec;
        vec.push_back(temp);
        this->bindValue[value] = vec;
    }
}

/**
 * Function name: updateSymbolTableValue
 * The input: string, double
 * The output: none
 * The function operation: The function updates the symbol table
 * Inserts the value of the given var (string name) , the value to the table
 * And initialize the bool sign to true, so we would know it exists.
 * @param name given var
 * @param value the value we want to update
 */
void SymbolTable::updateSymbolTableValue(string name, double value) {
    mutex mtx;
    unique_lock<mutex> lock(mtx);
    this->valueTable[name]->setInitialize(true);
    this->valueTable[name]->setValue(value);
}

/**
 * Function name: getSymbolTableDest
 * The input: string
 * The output: string
 * The function operation: The function returns the destination value of a given variable
 * If the variable doesn't exists, throws exception
 * @param name given var
 * @return string
 */
string SymbolTable::getSymbolTableDest(string name) {
    if (this->destTable[name]->checkIfInitialize()) {
        return this->destTable[name]->getValue();
    }
    throw "The variable does not Initialize";
}

/**
 * Function name: getSymbolTableValue
 * The input: string
 * The output: double
 * The function operation: The function returns the value of a variable
 * If it doesn't exists, throws exception
 * @param name given var
 * @return double
 */
double SymbolTable::getSymbolTableValue(string name) {
    if (this->valueTable[name]->checkIfInitialize()) {
        return this->valueTable[name]->getValue();
    }
    throw "The variable does not Initialize";
}

/**
 * Function name: getVariableForUpdate
 * The input: string
 * The output: vector<string>
 * The function operation: The function returns the variable (key), given the bind value
 * @param key string
 * @return vector<string>
 */
vector<StoreVarValue<double> *> SymbolTable::getVariablesForUpdate(
        string &key) {
    return this->bindValue[key];
}

bool SymbolTable::existsInDestMap(string var) {
    if (this->destTable.count(var) == ONE) {
        return true;
    }
    return false;
}

/**
 * Function name: existsInBindTableMap
 * The input: string
 * The output: none
 * The function operation: The function checks if var exists in the bindValue table
 * if yes, returns true, else returns false
 * @param var string
 * @return bool
 */
bool SymbolTable::existsInBindValueMap(string var) {
    if (this->bindValue.count(var) == ONE) {
        return true;
    }
    return false;
}

/**
 * Function name: existsInValueTableMap
 * The input: string
 * The output: none
 * The function operation: The function checks if var exists in the value table
 * if yes, returns true, else returns false
 * @param var string
 * @return bool
 */
bool SymbolTable::existsInValueTableMap(string var) {
    if (this->valueTable.count(var)) {
        return true;
    }
    return false;
}

/**
 * Function name: ~SymbolTable
 * The input: none
 * The output: none
 * The function operation: Destructs the SymbolTable
 */
SymbolTable::~SymbolTable() {
    map<string, StoreVarValue<string> *>::iterator itDe = this->destTable.begin();
    while (itDe != this->destTable.end()) {
        delete (itDe->second);
        itDe++;
    }
    map<string, StoreVarValue<double> *>::iterator itVa = this->valueTable.begin();
    while (itVa != this->valueTable.end()) {
        delete (itVa->second);
        itVa++;
    }
}

map<string, vector<StoreVarValue<double>*>> SymbolTable::getBindMap() {
    return  this->bindValue;
}

