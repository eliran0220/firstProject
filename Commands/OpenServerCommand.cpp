#include "OpenServerCommand.h"

/**
 * Function name: execute
 * The function operation: The function open a new server.
 * First we calculate the port and the reading rate from the parameters using
 * the calculate function Second, we create a new thread and send the run
 * function of the server, with the port, rate, and symbtol table
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
    // create socket and stop the program until the connection is made
    int socket = DataReaderServer::createSocket(port);
    delete (p);
    delete (r);
    // open a new thread for the server.
    this->serverThread = thread(DataReaderServer::run, socket, rate,
                                this->symbolTable, &this->shouldStop);
    return AMOUNT_SERVER_MOVEMENT;
}

/**
 * Function name: OpenServerCommand
 * The function operation: Constructs a new OpenServerCommand
 * @param expression given expression
 * @param symbolTable given symbol table
 */
OpenServerCommand::OpenServerCommand(Factory *expression,
                                     SymbolTable * &symbolTable) {
    this->factoryExpression = expression;
    this->symbolTable = symbolTable;
    this->shouldStop = false;
}

/**
 * Function name: ~OpenServerCommand
 * The function operation: Destructs the OpenServerCommand
 */
OpenServerCommand::~OpenServerCommand() {
    // stop the threads.
    this->shouldStop = true;
    this->serverThread.join();
}