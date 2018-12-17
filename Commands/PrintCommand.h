//
// Created by eliran on 12/15/18.
//

#ifndef FIRSTPROJECT_PRINTCOMMAND_H
#define FIRSTPROJECT_PRINTCOMMAND_H

#include"string"
#include "Command.h"
#include "../Useful/CastStringToExpression.h"
#include "FactoryCommands.h"
using namespace std;

class PrintCommand : public Command{
private:
    CastStringToExpression* castStringToExpression;
public:
    PrintCommand(CastStringToExpression* castStringToExpression);
    int execute(const vector<string> &parameters, int position);

};


#endif //FIRSTPROJECT_PRINTCOMMAND_H
