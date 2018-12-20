//
// Created by afik on 12/20/18.
//

#include "WhileCommmand.h"

int WhileCommand::execute(vector<string> &parameters, int position) {
    int returnPosition;
    bool flagCondition = this->condition(parameters[position + 1]);
    if (flagCondition && this->listOfCommands.empty()) {
        returnPosition = this->parser(&parameters, position + 3);
    } else if(!flagCondition) {
        return findTheEndBlock(&parameters, position + 3) - position;
    }
    while (this->condition(parameters[position + 1])) {
        for (int i = 0; i < this->listOfCommands.size(); ++i) {
            this->listOfCommands[i]->calculate();
        }
    }
    return returnPosition - position;
}