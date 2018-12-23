#include "ConditionParser.h"

/**
 * Function name: ConditionParser
 * The function operation: Constructs a new ConditionParser
 * @param factoryCommand factoryCommand
 * @param factoryExpression factoryExpression
 */
ConditionParser::ConditionParser(Factory *factoryCommand, Factory *factoryExpression) {
    this->factoryCommand = factoryCommand;
    this->factoryExpression = factoryExpression;
}

/**
 * Function name: ~ClientCommand
 * The function operation: Destructs the ClientCommand
 */
ConditionParser::~ConditionParser() {
    for (int i = this->listOfCommands.size() - 1; i >= 0; --i) {
        delete (this->listOfCommands[i]);
    }
}

/**
 * Function name: splitCondition
 * The function operation: The function splits the given string, by the given other string.
 * It finds
 * @param condition string
 * @param opera string
 * @return string
 */
vector<Expression *> ConditionParser::splitCondition(string &condition, string opera) {
    regex r("[0-9A-Za-z_]+(>||<||>=||<=||==||!=)[0-9A-Za-z_]+");
    // check if the condition string is legal
    if (!regex_match(condition, r)) {
        throw "Syntax error invalid condition";
    }
    vector<Expression *> vec;
    string item;
    stringstream ss(condition);
    Expression *temp = nullptr;
    int start = (int) condition.find(opera);
    item = condition.substr(0, start);
    temp = this->factoryExpression->create(item);
    vec.push_back(temp);
    item = condition.substr(start + opera.size(), condition.size());
    temp = this->factoryExpression->create(item);
    vec.push_back(temp);
    return vec;
}

/**
 * Function name: parser
 * The function operation: The function creates, and "calculates" the commands in the commands vector,
 * as long as the command at the position is not " } "
 * In the end, returns the position + 1, to move on to the next command
 * @param commands vector<string>
 * @param position int
 * @return int
 */
int ConditionParser::parser(vector<string> *commands, int position) {
    // while the block not ended
    while (commands->at(position) != "}") {
        Expression *tempCommand = this->factoryCommand->create(commands->at(position));
        tempCommand->setLexerStringAndPosition(commands, position);
        position += tempCommand->calculate();
        // add to the command list for reuse
        this->listOfCommands.push_back(tempCommand);
    }
    return position + 1;
}

/**
 * Function name: condition

 * The function operation: The function returns the result between operator of the expressions.
 * Depending on the given string, we do invoke the right operator to evaluate the expression, and
 * return the result.
 * @param conditionString string
 * @return bool
 */
bool ConditionParser::condition(string conditionString) {
    vector<Expression *> vec;
    bool resualt;
    if (strstr(conditionString.c_str(), ">")) {
        vec = splitCondition(conditionString, ">");
        resualt = vec[0]->operator>(vec[1]);
    } else if (strstr(conditionString.c_str(), ">=")) {
        vec = splitCondition(conditionString, ">=");
        resualt = vec[0]->operator>=(vec[1]);
    } else if (strstr(conditionString.c_str(), "<")) {
        vec = splitCondition(conditionString, "<");
        resualt = vec[0]->operator<(vec[1]);
    } else if (strstr(conditionString.c_str(), "<=")) {
        vec = splitCondition(conditionString, "<=");
        resualt = vec[0]->operator<=(vec[1]);
    } else if (strstr(conditionString.c_str(), "==")) {
        vec = splitCondition(conditionString, "==");
        resualt = vec[0]->operator==(vec[1]);
    } else if (strstr(conditionString.c_str(), "!=")) {
        vec = splitCondition(conditionString, "!=");
        resualt = vec[0]->operator!=(vec[1]);
    } else {
        throw "Syntax error invalid condition";
    }
    for (int i = (int) vec.size() - 1; i >= 0; --i) {
        delete (vec[i]);
    }
    return resualt;
}

/**
 * Function name: findTheEndBlock
 * The function operation: The function goes thorugh the strings in the parameters vector:
 * First it recognizes where the first { is at, then iterates thouugh the vector and funds the last
 * position of the } ,which is connected to the first { and returns it.
 * Used to know nested loops end (or nested if)
 * @param parameters vector<string>
 * @param position int
 * @return int
 */
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

