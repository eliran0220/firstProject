//
// Created by eliran on 12/19/18.
//

#ifndef FIRSTPROJECT_IFCOMMAND_H
#define FIRSTPROJECT_IFCOMMAND_H


#include "ConditionParser.h"

class IfCommand : ConditionParser {
public:

    int execute(const vector<string> &parameters, int position);
    vector<string>
    defineBlockOfCommands(const vector<string> &parameters);
};


#endif //FIRSTPROJECT_IFCOMMAND_H
