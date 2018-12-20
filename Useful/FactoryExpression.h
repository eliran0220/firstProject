//
// Created by afik on 12/15/18.
//

#ifndef FIRSTPROJECT_CASTSTRINGTOEXPRESSION_H
#define FIRSTPROJECT_CASTSTRINGTOEXPRESSION_H

#include <regex>
#include <queue>
#include "../Expressions/Div.h"
#include "../Expressions/Mult.h"
#include "../Expressions/Plus.h"
#include "../Expressions/Minus.h"
#include "../Expressions/Number.h"
#include "SymbolTable.h"
#include "Factory.h"

using namespace std;

class FactoryExpression : public Factory {

private:
    SymbolTable* symbolTable;
public:
    FactoryExpression(SymbolTable* symbolTable) {
        this->symbolTable = symbolTable;
    }

    vector<string> splitExpression(string stringExpression);

    Expression* createExpressionFromStrings(vector<string> strings);
    virtual Expression* create(const string& exString);
};


#endif //FIRSTPROJECT_CASTSTRINGTOEXPRESSION_H
