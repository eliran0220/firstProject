#include "WhileCommmand.h"

/**
 * Function name: execute
 * The function operation: The function checks if the condition is valid
 * first, if so, returnPosition is set to be the first position of first
 * command in the parser (if not valid, we check where the block ends and
 * continue from there)
 * Then, while the condition is valid, we run any command in the block.
 * Lastly, we return the right position we need to continue from
 * @param parameters vector<string>
 * @param position int
 * @return int
 */
int WhileCommand::execute(vector<string> &parameters, int position) {
    vector<Expression *> expressions;
    bool flagCondition = this->condition(parameters[position + 1]);
    if (flagCondition && expressions.empty()) {
        expressions = this->parser(&parameters, position + 3);
        // if the user input exit command free the memory and finish the loop
        if (loopPosition == EXIT_VALUE) {
            this->freeExpressionMemory(expressions);
            return this->loopPosition;
        }
    } else if (!flagCondition) {
        return findTheEndBlock(&parameters, position + 3) - position;
    }
    // do the command list again.
    while (this->condition(parameters[position + 1])) {
        for (int i = 0; i < (int)expressions.size(); ++i) {
            expressions[i]->calculate();
        }
    }
    this->freeExpressionMemory(expressions);
    return this->loopPosition - position;
}