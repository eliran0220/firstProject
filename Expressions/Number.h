//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_NUMBER_H
#define FIRSTPROJECT_NUMBER_H

#include "Expression.h"

class Number : public Expression {
    double number;
public:
    /**
     * Function name: Number
     * The input: double
     * The output: none
     * The function operation: Constructs a new Number Expression
     * @param number double
     */
    Number(double number) {
        this->number = number;
    }

    /**
     * Function name: calculate
     * The input: none
     * The output: double
     * The function operation: The function returns the number
     * and right expression
     * @return double
     */
    virtual double calculate() { return this->number; }
};

#endif //FIRSTPROJECT_NUMBER_H
