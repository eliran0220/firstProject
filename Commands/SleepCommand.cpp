#include "SleepCommand.h"

/**
 * Function name: SleepCommand
 * The function operation: Constructs a new SleepCommand
 * @param castStringToExpression given castStringToExpression
 */
SleepCommand::SleepCommand(Factory *castStringToExpression) {
    this->createExpression = castStringToExpression;
}

/**
 * Function name: execute
 * The function operation: The function creates an expression from parameters
 * in position + 1 and then sleeps for the time, evaluated , and divided by
 * 1000 (to turn into millieseconds)Lastly, we return 2 to move to the next
 * command in parser
 * @param parameters vector<string>
 * @param position int
 * @return int
 */
int SleepCommand::execute(vector<string> &parameters, int position) {
    Expression *e = this->createExpression->create(parameters[position + 1]);
    sleep(static_cast<unsigned int>(e->calculate() / MILLI_SECONDS));
    delete (e);
    return AMOUNT_MOVEMENT;
}



