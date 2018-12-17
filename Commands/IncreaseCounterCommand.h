//
// Created by afik on 12/17/18.
//

#ifndef FIRSTPROJECT_INCREASECOUNTECOMMAND_H
#define FIRSTPROJECT_INCREASECOUNTECOMMAND_H

#include "Command.h"
#define INCREASE_VALUE 1

class IncreaseCounterCommand : public Command {

public:
    IncreaseCounterCommand(){}

    int execute(const vector<string> &parameters, int position) {
        return INCREASE_VALUE;
    }
};
#endif //FIRSTPROJECT_INCREASECOUNTECOMMAND_H
