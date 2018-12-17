//
// Created by eliran on 12/17/18.
//


#include "DefineVarCommand.h"


int
DefineVarCommand::execute(const vector<string> &parameters, int position

) {
    string var = parameters[position + 1];
    this->table->addToDestTable(var,"");
    return 3;

}

DefineVarCommand::DefineVarCommand(
        CastStringToExpression *castStringToExpression,
        SymbolTable *symbolTable) {
    this->castStringToExpression = castStringToExpression;
    this->table = symbolTable;

}

