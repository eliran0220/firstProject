#ifndef IFCOMMAND_H
#define IFCOMMAND_H

#include "ConditionParser.h"

/*
 * If command class: the class is supposed to check if the condition is valid
 */
class IfCommand : public ConditionParser {
public:
    IfCommand(Factory* factoryCommand, Factory* factoryExpression):
    ConditionParser(factoryCommand, factoryExpression){}
    int execute(vector<string> &parameters, int position);
};


#endif
