#ifndef ENTERCCOMMAND_H
#define ENTERCCOMMAND_H

#include <iostream>
#include "Command.h"

#define AMOUNT_MOVEMENT 1

/**
 * The aim of the class is to stop the program untill it gets an input
 * from the user
 */
class EntercCommand : public Command {
public:
    EntercCommand();

    virtual int execute(vector<string> &parameters, int position);
};

#endif
