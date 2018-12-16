//
// Created by afik on 12/16/18.
//

#ifndef FIRSTPROJECT_COLLECTIONCOMMANDS_H
#define FIRSTPROJECT_COLLECTIONCOMMANDS_H

#include "../Commands/FactoryCommands.h"
#include "../Expressions/Expression.h"

class CollectionCommands {
private:
    map<string, Expression*> commands;
    FactoryCommands* factoryCommands;
public:
    CollectionCommands(){}
    ~CollectionCommands();

    Expression* getExpressionCommand(const string &command);
};


#endif //FIRSTPROJECT_COLLECTIONCOMMANDS_H
