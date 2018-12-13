//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_MINUS_H
#define FIRSTPROJECT_MINUS_H

#include "BinaryExpression.h"

class Minus: public BinaryExpression{
public:
    Minus(Expression* left, Expression* right): BinaryExpression(left, right){}
    virtual double calculate() {
        return this->left->calculate() - this->right->calculate();
    }
};
#endif //FIRSTPROJECT_MINUS_H
