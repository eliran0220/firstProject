#ifndef DEFINEVARCOMMAND_H
#define DEFINEVARCOMMAND_H

#include "Command.h"
#include "../Useful/FactoryExpression.h"
#define AMOUNT_MOVEMENT 2

#include <map>
class DefineVarCommand : public Command{
private:
    SymbolTable * table;
public:
    DefineVarCommand(SymbolTable* symbolTable);
    int execute(vector<string> &parameters, int position);

};


#endif

