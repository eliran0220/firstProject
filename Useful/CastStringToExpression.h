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

using namespace std;

class CastStringToExpression {
public:
    // להעביר בקונסטרקור את האובייקט המכיל את המשתנים הגלובלים שכול קומםאנד יחזיק
    CastStringToExpression() {}

    Expression* createExpression(const string& exString);
};


#endif //FIRSTPROJECT_CASTSTRINGTOEXPRESSION_H
