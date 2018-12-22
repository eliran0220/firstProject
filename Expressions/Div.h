//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_DIV_H
#define FIRSTPROJECT_DIV_H

#include "BinaryExpression.h"

enum {
    ZERO
};

class Div : public BinaryExpression {
public:
    /**
     * Function name: Div
     * The input: Expression*, Expression*
     * The output: none
     * The function operation: Constructs a new Div BinaryExpression
     * @param left expression
     * @param right expression
     */
    Div(Expression *left, Expression *right) : BinaryExpression(left, right) {}

    /**
     * Function name: calculate
     * The input: none
     * The output: double
     * The function operation: The function evaluates the result of the division between left expression
     * and right expression
     * @return double
     */
    virtual double calculate() {
        if (this->right->calculate() == ZERO) {
            throw "Error dividing by zero is undefined";
        }
        return this->left->calculate() / this->right->calculate();
    }
};

#endif //FIRSTPROJECT_DIV_H
