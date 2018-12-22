//
// Created by eliran on 12/20/18.
//

#include <pthread.h>
#include <thread>
#include "OpenServerCommand.h"
#include <mutex>



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

OpenServerCommand::OpenServerCommand(Factory *expression,
                                     SymbolTable *symbolTable) {
    this->factoryExpression = expression;
    this->symbolTable = symbolTable;
    this->shouldStop = false;
}

OpenServerCommand::~OpenServerCommand() {
    this->shouldStop = true;
}