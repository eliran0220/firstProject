#ifndef NUMBER_H
#define NUMBER_H

#include "Expression.h"

/**
 * Number class: The Number class is supposed to create a number from
 * expression
 */
class Number : public Expression {
    double number;
public:
    /**
     * Function name: Number
     * The function operation: Constructs a new Number Expression
     * @param number double
     */
    Number(double number) {
        this->number = number;
    }

    /**
     * Function name: calculate
     * The function operation: The function returns the number
     * and right expression
     * @return double
     */
    virtual double calculate() { return this->number; }
};

#endif
