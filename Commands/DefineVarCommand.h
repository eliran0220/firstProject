//
// Created by eliran on 12/15/18.
//

#ifndef FIRSTPROJECT_DEFINEVARCOMMAND_H
#define FIRSTPROJECT_DEFINEVARCOMMAND_H

#include "Command.h"

class DefineVarCommand : public Command {
public:
    DefineVarCommand();

    int execute(const vector<string> &parameters, int position) override;

};


#endif //FIRSTPROJECT_DEFINEVARCOMMAND_H
