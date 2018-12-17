//
// Created by afik on 12/17/18.
//

#ifndef FIRSTPROJECT_FACTORY_H
#define FIRSTPROJECT_FACTORY_H

#include "../Expressions/Expression.h"

class Factory {
public:
    virtual Expression* create(const string& exString) = 0;

    virtual ~Factory(){}
};
#endif //FIRSTPROJECT_FACTORY_H
