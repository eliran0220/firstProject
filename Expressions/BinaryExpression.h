//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_BINARYEXPRESSION_H
#define FIRSTPROJECT_BINARYEXPRESSION_H

#include "Expression.h"


class BinaryExpression : public Expression {
protected:
    Expression *left;
    Expression *right;
public:
    /**
     * Function name: BinaryExpression
     * The input: Expression*, Expression*
     * The output: none (constructor)
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
     * The input: none
     * The output: double
     * The function operation: Calculates the value of an expression
     * @return double
     */
    virtual double calculate() = 0;

    /**
     * Function name: ~BinaryExpression
     * The input: none
     * The output: none
     * The function operation: Destructs the binary expression
     */
    virtual ~BinaryExpression() {
        delete (left);
        delete (right);
    }

};


#endif //FIRSTPROJECT_BINARYEXPRESSION_H
