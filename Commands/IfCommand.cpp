#include "IfCommand.h"

/**
 * Function name: execute
 * The function operation: The function checks if the condition is valid,if so
 * executes all the commands in the block, if not, finds where t he block ends and continues from there.
 * @param parameters vector<string>
 * @param position int
 * @return int
 */
int IfCommand::execute(vector<string> &parameters, int position) {
    vector<Expression *> expressions;
    // check if the condition is valid
    if (this->condition(parameters[position + 1])) {
        expressions = this->parser(&parameters, position + 3);
        this->freeExpressionMemory(expressions);
        if (this->loopPosition == EXIT_VALUE) {
            return EXIT_VALUE;
        }
        return this->loopPosition - position;
    } else {
        // return the next position
        return findTheEndBlock(&parameters, position + 3) - position;
    }
}