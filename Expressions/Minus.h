#ifndef MINUS_H
#define MINUS_H

#include "BinaryExpression.h"

/**
 * Minus class: The Minus class is supposed to make minus expression, between
 * two other expressions, also has the calculate method to evaluate the
 * result
 */
class Minus : public BinaryExpression {
public:
    /**
     * Function name: Minus
     * The function operation: Constructs a new Minus BinaryExpression
     * @param left expression
     * @param right expression
     */
    Minus(Expression *left, Expression *right) : BinaryExpression(left,
                                                                  right) {}

    /**
     * Function name: calculate
     * The function operation: The function evaluates the result of the minus
     * between left expression and right expression
     * @return double
     */
    virtual double calculate() {
        return this->left->calculate() - this->right->calculate();
    }
};

#endif
