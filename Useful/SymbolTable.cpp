#include "SymbolTable.h"

mutex mtx;

/**
 * Function name: addToTable
 * The function operation: The function adds the given string to the maps.
 * The string represents the variable which will be added
 * @param name given string
 */
void SymbolTable::addToTable(string name) {
    unique_lock<mutex> lock(mtx);
    //StoreVarValue<string> *tempD = new StoreVarValue<string>("");
    //StoreVarValue<double> *tempV = new StoreVarValue<double>(0);
    this->valueTable[name] = 0;
    this->destTable[name] = "";
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
    unique_lock<mutex> lock(mtx);
    //this->destTable[name]->setInitialize(true);
    //this->valueTable[name]->setInitialize(true);
    //this->destTable[name]->setValue(value);
    //StoreVarValue<double> *temp = this->valueTable[name];
    // update map of simulator
    if (this->existsInBindValueMap(value)) {
        this->bindValue[value].push_back(name);
    } else {
        vector<string> vec;
        vec.push_back(name);
        this->bindValue[value] = vec;
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
    unique_lock<mutex> lock(mtx);
    //this->valueTable[name]->setInitialize(true);
    this->valueTable[name] = value;
}

/**
 * Function name: getSymbolTableDest
 * The function operation: The function returns the destination value of a given variable
 * If the variable doesn't exists, throws exception
 * @param name given var
 * @return string
 */
string SymbolTable::getSymbolTableDest(string name) {
    unique_lock<mutex> lock(mtx);
    //if (this->destTable[name]->checkIfInitialize()) {
        return this->destTable[name];
    //}
    throw "The variable does not Initialize";
}

/**
 * Function name: getSymbolTableValue
 * The function operation: The function returns the value of a variable
 * If it doesn't exists, throws exception
 * @param name given var
 * @return double
 */
double SymbolTable::getSymbolTableValue(string name) {
    unique_lock<mutex> lock(mtx);
    //if (this->valueTable[name]->checkIfInitialize()) {
        double x = this->valueTable[name];
        return x;
    //}
    //throw "The variable does not Initialize";
}

/**
 * Function name: getVariableForUpdate
 * The function operation: The function returns the variable (key), given the bind value
 * @param key string
 * @return vector<string>
 */


vector<string> SymbolTable::getVariablesForUpdate(
        string &key) {
    unique_lock<mutex> lock(mtx);
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
    /*
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
     */
}

/**
 * Function name: getBindMap
 * The function operation: The function returns a map which represents
 * the strings as their key, and values are double (the destination to
 * value map)
 * @return map<string, vector<StoreVarValue<double>*>>
 */
map<string, vector<string>> SymbolTable::getBindMap() {
    unique_lock<mutex> lock(mtx);
    return  this->bindValue;
}

