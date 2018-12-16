//
// Created by eliran on 12/15/18.
//

#ifndef FIRSTPROJECT_SLEEPCOMMAND_H
#define FIRSTPROJECT_SLEEPCOMMAND_H

#include <vector>
#include <string>
#include "Command.h"
#include "../Useful/CastStringToExpression.h"

using namespace std;

class SleepCommand : public Command {
private:
    CastStringToExpression* castStringToExpression;

public:
    SleepCommand(CastStringToExpression* castStringToExpression);
    int execute(const vector<string> &parameters, int position);

};


#endif //FIRSTPROJECT_SLEEPCOMMAND_H
