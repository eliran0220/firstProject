//
// Created by eliran on 12/17/18.
//


#include "DefineVarCommand.h"


int DefineVarCommand::execute(const vector<string> &parameters, int position) {
    string var = parameters[position + 1];
    this->table->addToDestTable(var,"");
    return position+2;

}

DefineVarCommand::DefineVarCommand(SymbolTable *symbolTable) {
    this->table = symbolTable;
}

