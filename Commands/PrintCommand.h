//
// Created by eliran on 12/15/18.
//

#ifndef FIRSTPROJECT_PRINTCOMMAND_H
#define FIRSTPROJECT_PRINTCOMMAND_H

#include"string"
#include "Command.h"
#include "../Useful/Factory.h"
#include "FactoryCommands.h"
using namespace std;

class PrintCommand : public Command{
private:
    Factory* createExpression;
public:
    PrintCommand(Factory* createExpression);
    virtual int execute(vector<string> &parameters, int position);

};


#endif //FIRSTPROJECT_PRINTCOMMAND_H
