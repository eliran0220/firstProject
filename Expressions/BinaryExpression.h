//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_BINARYEXPRESSION_H
#define FIRSTPROJECT_BINARYEXPRESSION_H

#include "Expression.h"


class BinaryExpression: public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryExpression(Expression* left, Expression* right) {
        this->left = left;
        this->right = right;
    }

    virtual double calculate() = 0;

    virtual ~BinaryExpression() {
        delete (left);
        delete(right);
    }

};




#endif //FIRSTPROJECT_BINARYEXPRESSION_H
