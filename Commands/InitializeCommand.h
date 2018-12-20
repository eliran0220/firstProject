//
// Created by eliran on 12/17/18.
//

#ifndef FIRSTPROJECT_INITIALIZECOMMAND_H
#define FIRSTPROJECT_INITIALIZECOMMAND_H


#include "Command.h"
#include "../Useful/Factory.h"
#include "../Useful/SymbolTable.h"

class InitializeCommand : public Command{
private:
    Factory * expression;
    SymbolTable * table;

public:
    InitializeCommand(Factory * expression, SymbolTable * table);
    virtual int execute(vector<string> &parameters, int position);
};


#endif //FIRSTPROJECT_INITIALIZECOMMAND_H
