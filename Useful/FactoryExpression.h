#ifndef CASTSTRINGTOEXPRESSION_H
#define CASTSTRINGTOEXPRESSION_H

#include <regex>
#include <iostream>
#include <queue>
#include "../Expressions/Div.h"
#include "../Expressions/Mult.h"
#include "../Expressions/Plus.h"
#include "../Expressions/Minus.h"
#include "../Expressions/Number.h"
#include "SymbolTable.h"
#include "Factory.h"

using namespace std;

/**
 * The class holds the responsability, of splitting the given string
 * and create the desirable expression from it.
 */
class FactoryExpression : public Factory {

private:
    SymbolTable *symbolTable;
public:
    FactoryExpression(SymbolTable * &symbolTable) {
        this->symbolTable = symbolTable;
    }

    vector<string> splitExpression(string stringExpression);

    Expression *createExpressionFromStrings(vector<string> strings);

    virtual Expression *create(const string &exString);
};


#endif
