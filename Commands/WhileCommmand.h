//
// Created by afik on 12/20/18.
//

#ifndef FIRSTPROJECT_WHILECOMMMAND_H
#define FIRSTPROJECT_WHILECOMMMAND_H


#include "ConditionParser.h"

class WhileCommand : public ConditionParser {

public:
    WhileCommand(Factory* factoryCommand, Factory* factoryExpression):
    ConditionParser(factoryCommand, factoryExpression){}

    virtual int execute(vector<string> &parameters, int position);
};


#endif //FIRSTPROJECT_WHILECOMMMAND_H
