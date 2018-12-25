#ifndef PRINTCOMMAND_H
#define PRINTCOMMAND_H

#include"string"
#include "Command.h"
#include "../Useful/Factory.h"
#include <iostream>
#include <regex>

#define AMOUNT_MOVEMENT 2

using namespace std;

/**
 * The PrintCommand class is in charger to print to the console.
 */
class PrintCommand : public Command {
private:
    Factory *createExpression;
public:
    PrintCommand(Factory *createExpression);

    virtual int execute(vector<string> &parameters, int position);

};

#endif
