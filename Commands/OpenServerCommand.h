//
// Created by eliran on 12/20/18.
//

#ifndef FIRSTPROJECT_OPENSERVERCOMMAND_H
#define FIRSTPROJECT_OPENSERVERCOMMAND_H


#include "Command.h"
#include "../Useful/Factory.h"
#include "../ServerAndClient/DataReaderServer.h"


class OpenServerCommand : public Command {
    Factory *expression;
public:
    OpenServerCommand(Factory *expression);

    int execute(vector<string> &parameters, int position) override;

};

#endif //FIRSTPROJECT_OPENSERVERCOMMAND_H
