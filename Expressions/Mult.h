#ifndef MULT_H
#define MULT_H

#include "BinaryExpression.h"

/**
 * Mult class: The Mult class is supposed to make multipication expression,
 * between two other expressions, also has the calculate method to evaluate the
 * result
 */
class Mult : public BinaryExpression {
public:
    /**
    * Function name: Mult
    * The function operation: Constructs a new Mult BinaryExpression
    * @param left expression
    * @param right expression
    */
    Mult(Expression *left, Expression *right) : BinaryExpression(left, right) {}

    /**
     * Function name: calculate
     * The function operation: The function evaluates the result of the multipication between left expression
     * and right expression
     * @return double
     */
    virtual double calculate() {
        return this->left->calculate() * this->right->calculate();
    }
};

#endif
