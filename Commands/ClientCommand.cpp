#include "ClientCommand.h"

/**
 * Function name: execute
 * The function operation: The function runs the client.
 * First it calculates the port and the ip (from the parameters, we know their positions)
 * then it checks if the ip is valid, if so, opens a thread and runs the server given the data above.
 * @param parameters vector<string>
 * @param position int
 * @return int
 */
int ClientCommand::execute(vector<string> &parameters, int position) {
    regex ipR("[0-9]*.[0-9]*.[0-9]*.[0-9]*");
    Expression *e = this->factoryExpression->create(parameters[position + 2]);
    int port = (int) e->calculate();
    string ip = parameters[position + 1];
    delete (e);
    // check if the ip address is legal
    if (regex_match(ip, ipR)) {
        thread serverThread(DataReaderClient::run, port, ip, this->symbolTable,
                            &this->shouldStop);
        serverThread.detach();
    } else {
        throw "Syntax error invalid ip address";
    }
    return AMOUNT_MOVEMENT;
}

/**
 * Function name: ClientCommand
 * The function operation: Constructs a new ClientCommand
 * @param symbolTable table
 * @param factoryExpression factoryExpression
 */
ClientCommand::ClientCommand(SymbolTable *symbolTable,
                             Factory *factoryExpression) {
    this->symbolTable = symbolTable;
    this->factoryExpression = factoryExpression;
    this->shouldStop = false;
}

/**
 * Function name: ~ClientCommand
 * The function operation: Destructs the ClientCommand
 */
ClientCommand::~ClientCommand() {
    this->shouldStop = true;
}