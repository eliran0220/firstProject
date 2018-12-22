//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_MINUS_H
#define FIRSTPROJECT_MINUS_H

#include "BinaryExpression.h"

class Minus: public BinaryExpression{
public:
    /**
     * Function name: Minus
     * The input: Expression*, Expression*
     * The output: none
     * The function operation: Constructs a new Minus BinaryExpression
     * @param left expression
     * @param right expression
     */
    Minus(Expression* left, Expression* right): BinaryExpression(left, right){}

    /**
     * Function name: calculate
     * The input: none
     * The output: double
     * The function operation: The function evaluates the result of the minus between left expression
     * and right expression
     * @return double
     */
    virtual double calculate() {
        return this->left->calculate() - this->right->calculate();
    }
};
#endif //FIRSTPROJECT_MINUS_H
