#ifndef OPENSERVERCOMMAND_H
#define OPENSERVERCOMMAND_H

#include "Command.h"
#include "../Useful/Factory.h"
#include "../ServerAndClient/DataReaderServer.h"
#include <pthread.h>
#include <thread>

#define AMOUNT_SERVER_MOVEMENT 3

/**
 * OpenServerCommand class: The OpenServerCommand class is supposed to open
 * the server
 */
class OpenServerCommand : public Command {
    Factory *factoryExpression;
    SymbolTable *symbolTable;
    thread serverThread;
    bool shouldStop;

public:
    OpenServerCommand(Factory *expression, SymbolTable * &symbolTable);

    ~OpenServerCommand();

    virtual int execute(vector<string> &parameters, int position);

};

#endif
