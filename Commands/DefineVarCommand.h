//
// Created by eliran on 12/17/18.
//


#ifndef FIRSTPROJECT_DEFINEVARCOMMAND_H
#define FIRSTPROJECT_DEFINEVARCOMMAND_H


#include "Command.h"
#include "../Useful/FactoryExpression.h"


#include <map>
class DefineVarCommand : public Command{
private:
    SymbolTable * table;
public:
    DefineVarCommand(SymbolTable* symbolTable);
    int execute(vector<string> &parameters, int position);

};


#endif //FIRSTPROJECT_DEFINEVARCOMMAND_H

