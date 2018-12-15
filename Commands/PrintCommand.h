//
// Created by eliran on 12/15/18.
//

#ifndef FIRSTPROJECT_PRINTCOMMAND_H
#define FIRSTPROJECT_PRINTCOMMAND_H

#include"string"
#include "Command.h"

using namespace std;

class PrintCommand : public Command{
private:
    string message;

public:
    void execute() override;

    PrintCommand(const string &message);
};


#endif //FIRSTPROJECT_PRINTCOMMAND_H
