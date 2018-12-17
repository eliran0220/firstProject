//
// Created by eliran on 12/17/18.
//


#ifndef FIRSTPROJECT_DEFINEVARCOMMAND_H
#define FIRSTPROJECT_DEFINEVARCOMMAND_H


#include "Command.h"
#include "../Useful/CastStringToExpression.h"
#include "FactoryCommands.h"

#include <map>
class DefineVarCommand : public Command{
private:
    CastStringToExpression* castStringToExpression;
    SymbolTable * table;
public:
    DefineVarCommand(CastStringToExpression* castStringToExpression,SymbolTable* symbolTable);
    int execute(const vector<string> &parameters, int position);

};


#endif //FIRSTPROJECT_DEFINEVARCOMMAND_H

