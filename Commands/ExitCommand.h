//
// Created by afik on 12/25/18.
//

#ifndef FIRSTPROJECT_EXITCOMMAND_H
#define FIRSTPROJECT_EXITCOMMAND_H


#include "Command.h"

#define EXIT_VALUE -1

class ExitCommand : public Command {
public:
    ExitCommand() {}
    int execute(vector<string> &parameters, int position);

};


#endif //FIRSTPROJECT_EXITCOMMAND_H
