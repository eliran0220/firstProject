//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_PLUS_H
#define FIRSTPROJECT_PLUS_H

#include "BinaryExpression.h"

class Plus: public BinaryExpression {
public:
    Plus(Expression* left, Expression* right): BinaryExpression(left, right) {}
    double calculate() {
        return this->right->calculate() + this->left->calculate();
    }
};
#endif //FIRSTPROJECT_PLUS_H
