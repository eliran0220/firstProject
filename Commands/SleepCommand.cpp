//
// Created by eliran on 12/15/18.
//

#include <unistd.h>
#define MILLI_SECONDS 1000
#include "SleepCommand.h"

int SleepCommand::execute(const vector<string> &parameters, int position) {
    CastStringToExpression c = CastStringToExpression();
    Expression* e = c.createExpression(parameters[position + 1]);
    sleep(static_cast<unsigned int>(e->calculate()/MILLI_SECONDS));
    delete(e);
    return position + 2;
}


