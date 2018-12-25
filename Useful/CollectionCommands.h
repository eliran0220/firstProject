#ifndef COLLECTIONCOMMANDS_H
#define COLLECTIONCOMMANDS_H

#include "../Commands/FactoryCommands.h"
#include "../Expressions/Expression.h"

/**
 * The class creates a new collection of commands, in which we will store
 * all our commands
 */
class CollectionCommands {
private:
    map<string, Expression *> commands;
    Factory *factoryCommands;

public:
    CollectionCommands();

    ~CollectionCommands();

    Expression *getExpressionCommand(const string &command);
};


#endif
