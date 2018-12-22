//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_MULT_H
#define FIRSTPROJECT_MULT_H

#include "BinaryExpression.h"

class Mult : public BinaryExpression {
public:
    /**
    * Function name: Mult
    * The input: Expression*, Expression*
    * The output: none
    * The function operation: Constructs a new Mult BinaryExpression
    * @param left expression
    * @param right expression
    */
    Mult(Expression *left, Expression *right) : BinaryExpression(left, right) {}

    /**
     * Function name: calculate
     * The input: none
     * The output: double
     * The function operation: The function evaluates the result of the multipication between left expression
     * and right expression
     * @return double
     */
    virtual double calculate() {
        return this->left->calculate() * this->right->calculate();
    }
};

#endif //FIRSTPROJECT_MULT_H
