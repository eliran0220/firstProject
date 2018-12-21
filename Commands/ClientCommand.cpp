//
// Created by afik on 12/22/18.
//

#include "ClientCommand.h"

int ClientCommand::execute(vector<string> &parameters, int position) {
    regex ipR("[0-9]*.[0-9]*.[0-9]*.[0-9]*");
    Expression* e = this->factoryExpression->create(parameters[position + 2]);
    int port = (int)e->calculate();
    string ip = parameters[position + 1];
    delete (e);
    if (regex_match(ip, ipR)){
        thread serverThread(DataReaderClient::run, port, ip, this->symbolTable,
                            &this->shouldStop);
        serverThread.detach();
    } else {
        throw "Syntax error invalid ip address";
    }
    return 3;
}

ClientCommand::ClientCommand(SymbolTable *symbolTable,
                             Factory *factoryExpression) {
    this->symbolTable = symbolTable;
    this->factoryExpression = factoryExpression;
    this->shouldStop = false;
}

ClientCommand::~ClientCommand() {
    this->shouldStop = true;
}