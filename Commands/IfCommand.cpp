//
// Created by eliran on 12/19/18.
//

#include "IfCommand.h"



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
