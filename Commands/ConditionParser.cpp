//
// Created by eliran on 12/19/18.
//

#include <sstream>
#include <cstring>
#include "ConditionParser.h"

ConditionParser::ConditionParser(Factory* factoryCommand, Factory* factoryExpression) {
    this->factoryCommand = factoryCommand;
    this->factoryExpression = factoryExpression;
}

ConditionParser::~ConditionParser() {
    for (int i = this->listOfCommands.size() - 1; i >= 0; --i) {
        delete(this->listOfCommands[i]);
    }
}


vector<Expression*> ConditionParser::splitCondition(string& condition, string opera) {
    vector<Expression*> vec;
    string item;
    stringstream ss(condition);
    Expression* temp = nullptr;
    int start = (int)condition.find(opera);
    item = condition.substr(0, start);
    temp = this->factoryExpression->create(item);
    vec.push_back(temp);
    item = condition.substr(start + opera.size(), condition.size());
    temp = this->factoryExpression->create(item);
    vec.push_back(temp);
    return vec;
}

int ConditionParser::parser(vector<string>* commands, int position) {
    while (commands->at(position) != "}") {
        Expression* tempCommand = this->factoryCommand->create(commands->at(position));
        tempCommand->setLexerStringAndPosition(commands, position);
        position += tempCommand->calculate();
        this->listOfCommands.push_back(tempCommand);
    }
    return position + 1;
}

bool ConditionParser::condition(string conditionString) {
    vector<Expression*> vec;
    bool resualt;
    if (strstr(conditionString.c_str(),">")) {
        vec = splitCondition(conditionString, ">");
        resualt = vec[0]->operator>(vec[1]);
    } else if (strstr(conditionString.c_str(),">=")) {
        vec = splitCondition(conditionString, ">=");
        resualt = vec[0]->operator>=(vec[1]);
    } else if (strstr(conditionString.c_str(),"<")) {
        vec = splitCondition(conditionString, "<");
        resualt = vec[0]->operator<(vec[1]);
    } else if (strstr(conditionString.c_str(),"<=")) {
        vec = splitCondition(conditionString, "<=");
        resualt = vec[0]->operator<=(vec[1]);
    } else if (strstr(conditionString.c_str(),"==")) {
        vec = splitCondition(conditionString, "==");
        resualt = vec[0]->operator==(vec[1]);
    }else if (strstr(conditionString.c_str(),"!=")) {
        vec = splitCondition(conditionString, "!=");
        resualt = vec[0]->operator!=(vec[1]);
    }
    for (int i = (int)vec.size() - 1; i >= 0; --i) {
        delete(vec[i]);
    }
    return resualt;
}

int ConditionParser::findTheEndBlock(vector<string> *parameters, int position) {
    int counter = 0;
    int amountBlock = 1;
    while (counter < amountBlock) {
        if (parameters->at(position) == "{") {
            amountBlock++;
        } else if (parameters->at(position) == "}") {
            counter++;
        }
        position++;
    }
    return position;
}

