//
// Created by eliran on 12/20/18.
//


#include "OpenServerCommand.h"



int OpenServerCommand::execute(vector<string> &parameters, int position) {
    Expression *p = this->expression->create(parameters[position+1]);
    Expression *r = this->expression->create(parameters[position+2]);
    int port = (int)(p->calculate());
    int rate = (int)(r->calculate());
    // להוסיף את הסימבול טייבל
    DataReaderServer *dataReaderServer = new DataReaderServer(port,rate, nullptr);
    dataReaderServer->run();
    return 3;

}

OpenServerCommand::OpenServerCommand(Factory *expression){
    this->expression = expression;
}
