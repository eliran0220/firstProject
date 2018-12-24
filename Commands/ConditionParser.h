//
// Created by eliran on 12/19/18.
//

#ifndef FIRSTPROJECT_CONDITIONPARSER_H
#define FIRSTPROJECT_CONDITIONPARSER_H


#include <sstream>
#include <cstring>
#include <regex>
#include "Command.h"
#include "../Useful/Factory.h"
#include "ExitCommand.h"

class ConditionParser : public Command {

protected:
    vector<Expression*> listOfCommands;
    Factory* factoryCommand;
    Factory* factoryExpression;
    int loopPosition;

public:
    ConditionParser(Factory* factoryCommand, Factory* factoryExpression);
    virtual ~ConditionParser();

    virtual int execute(vector<string> &parameters, int position) = 0;
    vector<Expression*> splitCondition(string& condition, string opera);

    bool condition(string conditionString);

    vector<Expression*> parser(vector<string>* commands, int position);

    void freeExpressionMemory(vector<Expression *> expression);

    int findTheEndBlock(vector<string> *parameters, int position);
};


#endif //FIRSTPROJECT_CONDITIONPARSER_H
