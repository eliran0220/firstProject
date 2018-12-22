//
// Created by eliran on 12/20/18.
//

#include <pthread.h>
#include <thread>
#include "OpenServerCommand.h"

/**
 * Function name: execute
 * The input: vector<string>, int
 * The output: int
 * The function operation: The function open a new server.
 * First we calcualte the port and the reading rate from the parameters using the calculate function
 * Second, we create a new thread and send the run function of the server, with the port, rate, and symbtol table
 * also, send a boolean value to know when to stop
 * @param parameters vector<string>
 * @param position int
 * @return int
 */
int OpenServerCommand::execute(vector<string> &parameters, int position) {
    Expression *p = this->factoryExpression->create(parameters[position + 1]);
    Expression *r = this->factoryExpression->create(parameters[position + 2]);
    int port = (int) (p->calculate());
    int rate = (int) (r->calculate());
    delete (p);
    delete (r);
    thread serverThread(DataReaderServer::run, port, rate, this->symbolTable,
                        &this->shouldStop);
    serverThread.detach();
    return 3;
}

/**
 * Function name: OpenServerCommand
 * The input: Factory*, SymbolTable*
 * The output: none
 * The function operation: Constructs a new OpenServerCommand
 * @param expression given expression
 * @param symbolTable given symbol table
 */
OpenServerCommand::OpenServerCommand(Factory *expression,
                                     SymbolTable *symbolTable) {
    this->factoryExpression = expression;
    this->symbolTable = symbolTable;
    this->shouldStop = false;
}

/**
 * Function name: ~OpenServerCommand
 * The input: none
 * The output: none
 * The function operation: Destructs the OpenServerCommand
 */
OpenServerCommand::~OpenServerCommand() {
    this->shouldStop = true;
}