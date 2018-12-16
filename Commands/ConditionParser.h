//
// Created by eliran on 12/16/18.
//

#ifndef FIRSTPROJECT_CONDITIONPARSER_H
#define FIRSTPROJECT_CONDITIONPARSER_H


#include "Command.h"

class ConditionParser : public Command{
public:
    int execute(const vector<string> &parameters, int position) override;

};


#endif //FIRSTPROJECT_CONDITIONPARSER_H
