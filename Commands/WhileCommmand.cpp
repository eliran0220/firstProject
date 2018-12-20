//
// Created by afik on 12/20/18.
//

#include "WhileCommmand.h"

int WhileCommand::execute(vector<string> &parameters, int position) {
    int returnPosition;
    if (this->condition(parameters[position + 1])) {
        returnPosition = this->parser(&parameters, position + 3);
    } else {
        return findTheEndBlock(&parameters, position + 3);
    }
    while (this->condition(parameters[position + 1])) {
        for (int i = 0; i < this->listOfCommands.size(); ++i) {
            this->listOfCommands[i]->calculate();
        }
    }
    return returnPosition;
}