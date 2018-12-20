//
// Created by eliran on 12/17/18.
//


#include "DefineVarCommand.h"


int DefineVarCommand::execute(vector<string> &parameters, int position) {
    string var = parameters[position + 1];
    this->table->addToTable(var);
    return 2;
}

DefineVarCommand::DefineVarCommand(SymbolTable *symbolTable) {
    this->table = symbolTable;
}

