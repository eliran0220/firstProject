#ifndef INCREASECOUNTECOMMAND_H
#define INCREASECOUNTECOMMAND_H

#include "Command.h"
#define INCREASE_VALUE 1

/**
 * The class is responsible of incrementing to the next position in the parser.
 */
class IncreaseCounterCommand : public Command {

public:
    IncreaseCounterCommand(){}

    virtual int execute(vector<string> &parameters, int position) {
        return INCREASE_VALUE;
    }
};
#endif
