#include "IfCommand.h"

/**
 * Function name: execute
 * The input: vector<string>, int
 * The output: none
 * The function operation: The function checks if the condition is valid,if so
 * executes all the commands in the block, if not, finds where t he block ends and continues from there.
 * @param parameters vector<string>
 * @param position int
 * @return int
 */
int IfCommand::execute(vector<string> &parameters, int position) {
    if (this->condition(parameters[position + 1])) {
        return this->parser(&parameters, position + 3) - position;
    } else {
        return findTheEndBlock(&parameters, position + 3) - position;
    }
}


/*
vector<string>
IfCommand::defineBlockOfCommands(vector<string> &parameters) {
    int counter = 0;
    vector<string> blockOfCommands;
    for (int i = 0; i < parameters.size(); i++) {
        if (parameters[i] == "{") {
            counter++;
        }
        if (parameters[i] == "}") {
            counter--;
            if (counter == 0) {
                blockOfCommands.push_back(parameters[i]);
                break;
            }
        }
        blockOfCommands.push_back(parameters[i]);
    }

}
 */
