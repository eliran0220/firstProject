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
    int execute(const vector<string> &parameters, int position) override;
};


#endif //FIRSTPROJECT_INITIALIZECOMMAND_H
