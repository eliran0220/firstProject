//
// Created by afik on 12/20/18.
//

#include "WhileCommmand.h"

/**
 * Function name: execute
 * The input: vector<string>, int
 * The output: int
 * The function operation: The function checks if the condition is valid first, if so, returnPosition is set
 * to be the first position of first command in the parser (if not valid, we check where the block ends and
 * continue from there)
 * Then, while the condition is valid, we run any command in the block.
 * Lastly, we return the right position we need to continue from
 * @param parameters vector<string>
 * @param position int
 * @return int
 */
int WhileCommand::execute(vector<string> &parameters, int position) {
    int returnPosition;
    bool flagCondition = this->condition(parameters[position + 1]);
    if (flagCondition && this->listOfCommands.empty()) {
        returnPosition = this->parser(&parameters, position + 3);
    } else if (!flagCondition) {
        return findTheEndBlock(&parameters, position + 3) - position;
    }
    while (this->condition(parameters[position + 1])) {
        for (int i = 0; i < this->listOfCommands.size(); ++i) {
            this->listOfCommands[i]->calculate();
        }
    }
    return returnPosition - position;
}