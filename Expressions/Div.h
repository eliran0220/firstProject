//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_DIV_H
#define FIRSTPROJECT_DIV_H

#include "BinaryExpression.h"
enum {ZERO};
class Div: public BinaryExpression{
public:
    Div(Expression* left, Expression* right): BinaryExpression(left, right) {}
    virtual double calculate() {
        if (this->right->calculate() == ZERO) {
            throw "Error dividing by zero is undefined";
        }
        return this->left->calculate() / this->right->calculate();
    }
};
#endif //FIRSTPROJECT_DIV_H
