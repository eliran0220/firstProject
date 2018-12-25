#ifndef SLEEPCOMMAND_H
#define SLEEPCOMMAND_H

#include <vector>
#include <string>
#include "Command.h"
#include "../Useful/Factory.h"
#include <unistd.h>

#define AMOUNT_MOVEMENT 2
#define MILLI_SECONDS 1000

using namespace std;

/**
 * SleepCommand class: The class is supposed to make the program sleep
 * for a period of time
 */
class SleepCommand : public Command {
private:
    Factory *createExpression;

public:
    SleepCommand(Factory *createExpression);

    virtual int execute(vector<string> &parameters, int position);

};

#endif
