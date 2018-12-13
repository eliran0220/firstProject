//
// Created by afik on 12/13/18.
//

#ifndef FIRSTPROJECT_NUMBER_H
#define FIRSTPROJECT_NUMBER_H

#include "Expression.h"

class Number: public Expression {
    double number;
public:
    Number(double number) {
        this->number = number;
    }

    virtual double calculate(){ return this->number;}
};
#endif //FIRSTPROJECT_NUMBER_H
