//
// Created by eliran on 12/19/18.
//

#include "IfCommand.h"



int IfCommand::execute(const vector<string> &parameters, int position) {

}

vector<string>
IfCommand::defineBlockOfCommands(const vector<string> &parameters) {
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
