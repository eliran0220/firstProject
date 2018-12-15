//
// Created by eliran on 12/15/18.
//

#include <iostream>
#include "PrintCommand.h"

void PrintCommand::execute() {
    cout << this->message;

}

PrintCommand::PrintCommand(const string &message) : message(message) {}
