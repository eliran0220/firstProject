#ifndef DIV_H
#define DIV_H

#include "BinaryExpression.h"

enum {ZERO};

/**
 * Div class: The Div class is supposed to make Divide expression, between
 * two other expressions, also has the calculate method to evaluate the
 * result
 */

class Div : public BinaryExpression {
public:
    /**
     * Function name: Div
     * The function operation: Constructs a new Div BinaryExpression
     * @param left expression
     * @param right expression
     */
    Div(Expression *left, Expression *right) : BinaryExpression(left, right) {}

    /**
     * Function name: calculate
     * The function operation: The function evaluates the result of the
     * division between left expression
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

#endif
