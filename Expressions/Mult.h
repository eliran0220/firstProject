//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_MULT_H
#define FIRSTPROJECT_MULT_H

#include "BinaryExpression.h"

class Mult: public BinaryExpression {
public:
    Mult(Expression* left, Expression* right): BinaryExpression(left, right){}
    virtual double calculate() {
        return this->left->calculate() * this->right->calculate();
    }
};
#endif //FIRSTPROJECT_MULT_H
