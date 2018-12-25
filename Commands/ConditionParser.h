#ifndef CONDITIONPARSER_H
#define CONDITIONPARSER_H

#include <sstream>
#include <cstring>
#include <regex>
#include "Command.h"
#include "../Useful/Factory.h"
#include "ExitCommand.h"

/**
 * ConditionParser class: The ConditionParser class is supposed to check
 * if the condition is valid
 */
class ConditionParser : public Command {

protected:
    vector<Expression *> listOfCommands;
    Factory *factoryCommand;
    Factory *factoryExpression;
    int loopPosition;

public:
    ConditionParser(Factory *factoryCommand, Factory *factoryExpression);

    virtual ~ConditionParser();

    virtual int execute(vector<string> &parameters, int position) = 0;

    vector<Expression *> splitCondition(string &condition, string opera);

    bool condition(string conditionString);

    vector<Expression *> parser(vector<string> *commands, int position);

    void freeExpressionMemory(vector<Expression *> expression);

    int findTheEndBlock(vector<string> *parameters, int position);
};

#endif
