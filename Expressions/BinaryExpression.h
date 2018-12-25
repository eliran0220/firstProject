#ifndef BINARYEXPRESSION_H
#define BINARYEXPRESSION_H

#include "Expression.h"

/**
 * BinaryExpression class: The BinaryExpression is supposed to create a
 * binary expression
 */
class BinaryExpression : public Expression {
protected:
    Expression *left;
    Expression *right;
public:
    /**
     * Function name: BinaryExpression
     * The function operation: Constructs a binary expression
     * @param left expression
     * @param right expression
     */
    BinaryExpression(Expression *left, Expression *right) {
        this->left = left;
        this->right = right;
    }

    /**
     * Function name: calculate
     * The function operation: Calculates the value of an expression
     * @return double
     */
    virtual double calculate() = 0;

    /**
     * Function name: ~BinaryExpression
     * The function operation: Destructs the binary expression
     */
    virtual ~BinaryExpression() {
        delete (left);
        delete (right);
    }

};


#endif
