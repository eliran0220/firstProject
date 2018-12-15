//
// Created by eliran on 12/15/18.
//

#include <iostream>
#include "PrintCommand.h"

int PrintCommand::execute(const vector<string> &parameters, int position) {
    cout << parameters[position + 1];
    return position + 1;
}

PrintCommand::PrintCommand(const string &message) : message(message) {}
