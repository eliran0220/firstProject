//
// Created by eliran on 12/15/18.
//

#include <unistd.h>

#define MILLI_SECONDS 1000

#include "SleepCommand.h"

/**
 * Function name: SleepCommand
 * The input: Factory*
 * The output: none
 * The function operation: Constructs a new SleepCommand
 * @param castStringToExpression given castStringToExpression
 */
SleepCommand::SleepCommand(Factory *castStringToExpression) {
    this->createExpression = castStringToExpression;
}

/**
 * Function name: execute
 * The input: vector<string>, int
 * The output: int
 * The function operation: The function creates an expression from parameters in position + 1
 * and then sleeps for the time, evaluated , and divided by 1000 (to turn into millieseconds)
 * Lastly, we return 2 to move to the next command in parser
 * @param parameters vector<string>
 * @param position int
 * @return int
 */
int SleepCommand::execute(vector<string> &parameters, int position) {
    Expression *e = this->createExpression->create(parameters[position + 1]);
    sleep(static_cast<unsigned int>(e->calculate() / MILLI_SECONDS));
    delete (e);
    return 2;
}



