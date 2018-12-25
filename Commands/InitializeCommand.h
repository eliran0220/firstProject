#ifndef INITIALIZECOMMAND_H
#define INITIALIZECOMMAND_H

#include "Command.h"
#include <algorithm>
#include <cstring>
#include "../Useful/Factory.h"
#include "../Useful/SymbolTable.h"

#define AMOUNT_MOVEMENT 2

/**
 * InitializeCommand class: The InitializeCommand class is supposed to
 * initialize the given vars
 */
class InitializeCommand : public Command {
private:
    Factory *expression;
    SymbolTable *table;

public:
    InitializeCommand(Factory *expression, SymbolTable *table);

    virtual int execute(vector<string> &parameters, int position);
};


#endif
