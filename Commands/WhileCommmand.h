#ifndef WHILECOMMMAND_H
#define WHILECOMMMAND_H


#include "ConditionParser.h"

/*
 * While command class: the class is supposed to check if the condition is
 * valid multiple times
 */
class WhileCommand : public ConditionParser {

public:
    WhileCommand(Factory *factoryCommand, Factory *factoryExpression) :
            ConditionParser(factoryCommand, factoryExpression) {}

    virtual int execute(vector<string> &parameters, int position);
};

#endif
