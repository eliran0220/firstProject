//
// Created by eliran on 12/19/18.
//

#ifndef FIRSTPROJECT_IFCOMMAND_H
#define FIRSTPROJECT_IFCOMMAND_H


#include "ConditionParser.h"

class IfCommand : public ConditionParser {
public:
    IfCommand(Factory* factoryCommand, Factory* factoryExpression):
    ConditionParser(factoryCommand, factoryExpression){}
    int execute(vector<string> &parameters, int position);
};


#endif //FIRSTPROJECT_IFCOMMAND_H
