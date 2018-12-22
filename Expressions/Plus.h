//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_PLUS_H
#define FIRSTPROJECT_PLUS_H

#include "BinaryExpression.h"

class Plus : public BinaryExpression {
public:
    /**
    * Function name: Plus
    * The input: Expression*, Expression*
    * The output: none
    * The function operation: Constructs a new Plus BinaryExpression
    * @param left expression
    * @param right expression
    */
    Plus(Expression *left, Expression *right) : BinaryExpression(left, right) {}

    /**
    * Function name: calculate
    * The input: none
    * The output: double
    * The function operation: The function evaluates the result of the adding of left expression
    * and right expression
    * @return double
    */
    double calculate() {
        return this->right->calculate() + this->left->calculate();
    }
};

#endif //FIRSTPROJECT_PLUS_H
