#ifndef DEFINEVARCOMMAND_H
#define DEFINEVARCOMMAND_H

#include "Command.h"
#include "../Useful/FactoryExpression.h"
#include <map>

#define AMOUNT_VAR_MOVEMENT 2

/**
 * DefineVarCommand: The DefineVarCommand is supposed to define a new var
 * in our program
 */
class DefineVarCommand : public Command {
private:
    SymbolTable *table;
public:
    DefineVarCommand(SymbolTable *symbolTable);

    int execute(vector<string> &parameters, int position);

};


#endif

