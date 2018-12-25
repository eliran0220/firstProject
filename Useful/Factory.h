#ifndef FACTORY_H
#define FACTORY_H

#include "../Expressions/Expression.h"

/**
 * The class represents a Factory, which is an abstract class.
 * Holds the function create, which will be the base of creating
 * an expression
 */
class Factory {
public:
    virtual Expression *create(const string &exString) = 0;

    virtual ~Factory() {}
};

#endif
