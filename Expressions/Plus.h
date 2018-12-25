#ifndef PLUS_H
#define PLUS_H

#include "BinaryExpression.h"

/**
 * Plus class: The Plus class is supposed to make plus expression,
 * between two other expressions, also has the calculate method to evaluate the
 * result
 */
class Plus : public BinaryExpression {
public:
    /**
    * Function name: Plus
    * The function operation: Constructs a new Plus BinaryExpression
    * @param left expression
    * @param right expression
    */
    Plus(Expression *left, Expression *right) : BinaryExpression(left, right) {}

    /**
    * Function name: calculate
    * The function operation: The function evaluates the result of
     * the adding of left expression
    * and right expression
    * @return double
    */
    double calculate() {
        return this->right->calculate() + this->left->calculate();
    }
};

#endif
