//
// Created by eliran on 12/15/18.
//

#ifndef FIRSTPROJECT_SLEEPCOMMAND_H
#define FIRSTPROJECT_SLEEPCOMMAND_H

#include <vector>
#include <string>
#include "Command.h"

using namespace std;

class SleepCommand : public Command {
private:
    double sleepFor;
public:
    void execute() override;

    SleepCommand(double sleepFor);

};


#endif //FIRSTPROJECT_SLEEPCOMMAND_H
