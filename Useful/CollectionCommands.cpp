//
// Created by afik on 12/16/18.
//

#include "CollectionCommands.h"

CollectionCommands::CollectionCommands() {
    this->factoryCommands = new FactoryCommands();
}


CollectionCommands::~CollectionCommands() {
    delete (this->factoryCommands);
    map<string, Expression*>::iterator it = this->commands.begin();
    while (it != this->commands.end()) {
        delete (it->second);
        it++;
    }
}

Expression* CollectionCommands::getExpressionCommand(const string &command) {
    int check = (int)this->commands.count(command);
    if (check == 1) {
        return this->commands[command];
    }
    Expression* exCommand = this->factoryCommands->create(command);
    this->commands[command] = exCommand;
    return exCommand;
}