//
// Created by afik on 12/23/18.
//

#ifndef FIRSTPROJECT_ENTERCCOMMAND_H
#define FIRSTPROJECT_ENTERCCOMMAND_H


#include "Command.h"

class EntercCommand: public Command {
public:
    EntercCommand();
    virtual int execute(vector<string> &parameters, int position);
};


#endif //FIRSTPROJECT_ENTERCCOMMAND_H
