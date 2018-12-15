//
// Created by eliran on 12/15/18.
//

#include <unistd.h>
#define MILLI_SECONDS 1000
#include "SleepCommand.h"

void SleepCommand::execute() {
    sleep(static_cast<unsigned int>(sleepFor/MILLI_SECONDS));
}

SleepCommand::SleepCommand(double sleepFor) : sleepFor(sleepFor) {}

