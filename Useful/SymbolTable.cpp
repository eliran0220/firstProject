#include <zconf.h>
#include "SymbolTable.h"


/**
 * Function name: addToTable
 * The function operation: The function adds the given string to the maps.
 * The string represents the variable which will be added
 * @param name given string
 */
void SymbolTable::addToTable(string name) {
    lock_guard<mutex> lock(mtx);
    StoreVarValue<string> *tempD = new StoreVarValue<string>("");
    StoreVarValue<double> *tempV = new StoreVarValue<double>(0);
    this->valueTable[name] = tempV;
    this->destTable[name] = tempD;
}

/**
 * Function name: updateSymbtolTableDest
 * The function operation: The function updates the table dest with the given string (name) to the
 * given string (value).
 * We initialize the name var in the dest, value, to true , so we would know it exists,
 * and then we set the value in the dest table.
 * @param name given string
 * @param value given string
 */
void SymbolTable::updateSymbolTableDest(string name, string value) {
    lock_guard<mutex> lock(mtx);
    this->destTable[name]->setInitialize(true);
    this->destTable[name]->setValue(value);
    if (this->existsInBindValueMap(value)) {
        this->bindValue[value].push_back(name);
    } else {
        vector<string> vec;
        vec.push_back(name);
        this->bindValue[value] = vec;
    }
    // wait for the variable update from the server.
    while (!this->valueTable[name]) {
        sleep(1);
    }
}

/**
 * Function name: updateSymbolTableValue
 * The function operation: The function updates the symbol table
 * Inserts the value of the given var (string name) , the value to the table
 * And initialize the bool sign to true, so we would know it exists.
 * @param name given var
 * @param value the value we want to update
 */
void SymbolTable::updateSymbolTableValue(string name, double value) {
    lock_guard<mutex> lock(mtx);
    this->valueTable[name]->setInitialize(true);
    this->valueTable[name]->setValue(value);
}

/**
 * Function name: getSymbolTableDest
 * The function operation: The function returns the destination value of a given variable
 * If the variable doesn't exists, throws exception
 * @param name given var
 * @return string
 */
string SymbolTable::getSymbolTableDest(string name) {
    return this->destTable[name]->getValue();
}

/**
 * Function name: getSymbolTableValue
 * The function operation: The function returns the value of a variable
 * If it doesn't exists, throws exception
 * @param name given var
 * @return double
 */
double SymbolTable::getSymbolTableValue(string name) {
    double x = this->valueTable[name]->getValue();
    return x;
}

/**
 * Function name: getVariableForUpdate
 * The function operation: The function returns the variable (key), given the bind value
 * @param key string
 * @return vector<string>
 */


vector<string>* SymbolTable::getVariablesForUpdate(
        string &key) {
    return &this->bindValue[key];
}

/**
 * Function name: existsInBindTableMap
 * The function operation: The function checks if var exists in the bindValue table
 * if yes, returns true, else returns false
 * @param var string
 * @return bool
 */
bool SymbolTable::existsInBindValueMap(string var) {
    if ((int)this->bindValue.count(var) == ONE) {
        return true;
    }
    return false;
}

/**
 * Function name: existsInValueTableMap
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

/**
 * Function name: varsToUpdate
 * The function operation: The function pushes the vars that need to be
 * updated to the needToUpdate map which inside a queue
 * @param name a given string
 * @param value a given value
 */
void SymbolTable::varsToUpdate(string name, double value) {
    map<string, double> temp;
    temp[name] = value;
    this->needToUpdate.push(temp);
    this->updateSymbolTableValue(name, value);
}

/**
 * Function name: getQueueToUpdate
 * The function operation: The function returns the queue
 * @return queue<map<string,double>>*
 */
queue<map<string, double>> *SymbolTable::getQueueToUpdate() {
    return &this->needToUpdate;
}