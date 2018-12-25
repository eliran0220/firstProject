#ifndef CLIENTCOMMAND_H
#define CLIENTCOMMAND_H

#include <regex>
#include <thread>
#include "Command.h"
#include "../Useful/SymbolTable.h"
#include "../Useful/Factory.h"
#include "../ServerAndClient/DataReaderClient.h"

#define AMOUNT_MOVEMENT 3

/**
 * ClientCommand class: The ClientCommand class is supposed to open a new
 * client
 */
class ClientCommand : public Command {
    SymbolTable *symbolTable;
    Factory *factoryExpression;
    bool shouldStop;
public:
    ClientCommand(SymbolTable *symbolTable, Factory *factoryExpression);

    ~ClientCommand();

    virtual int execute(vector<string> &parameters, int position);
};

#endif
