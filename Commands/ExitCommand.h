#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H
#define EXIT_VALUE -1

#include "Command.h"

/**
 * ExitCommand class: The ExitCommand class is supposed to make the command
 * exit after it's purpose has been completed
 */
class ExitCommand : public Command {
public:
    ExitCommand() {}

    int execute(vector<string> &parameters, int position);

};


#endif
