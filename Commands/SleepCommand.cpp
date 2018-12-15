//
// Created by eliran on 12/15/18.
//

#include <unistd.h>
#include "SleepCommand.h"
#define MILLI_SECONDS 1000

int SleepCommand::execute() {
    sleep(static_cast<unsigned int>(sleepFor/MILLI_SECONDS));
    return 2; // להתקדם שני שורות (לדלג גם על הקומאנד וגם על הערך שלו)
}

SleepCommand::SleepCommand(double sleepFor) : sleepFor(sleepFor) {}

