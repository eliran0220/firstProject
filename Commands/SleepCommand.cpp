//
// Created by eliran on 12/15/18.
//

#include <unistd.h>
#define MILLI_SECONDS 1000
#include "SleepCommand.h"

SleepCommand::SleepCommand(Factory *castStringToExpression){
    this->createExpression = castStringToExpression;
}
int SleepCommand::execute(const vector<string> &parameters, int position) {
    Expression* e = this->createExpression->create(parameters[position + 1]);
    sleep(static_cast<unsigned int>(e->calculate()/MILLI_SECONDS));
    delete(e);
    return position + 2;
}


