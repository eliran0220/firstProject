//
// Created by afik on 12/16/18.
//

#include "CollectionCommands.h"

/**
* Function name: CollectionCommands
* The input: none
* The output: none
* The function operation: Constructs a new CollectionCommand
*/
CollectionCommands::CollectionCommands() {
    this->factoryCommands = new FactoryCommands();
}

/**
 * Function name: ~CollectionCommands
 * The input: none
 * The output: none
 * The function operatin: Destructs the collection command
 */
CollectionCommands::~CollectionCommands() {
    delete (this->factoryCommands);
    map<string, Expression *>::iterator it = this->commands.begin();
    while (it != this->commands.end()) {
        delete (it->second);
        it++;
    }
}

/**
 * Function name: getExpressionCommand
 * The input: string
 * The output: Expression
 * The function operation: gets a string command, checks if the command exists in the collection,
 * if exists, returns it, if not, creates a new Expression of that command and returns it.
 * @param command a given string
 * @return Expression
 */
Expression *CollectionCommands::getExpressionCommand(const string &command) {
    int check = (int) this->commands.count(command);
    if (check == 1) {
        return this->commands[command];
    }
    Expression *exCommand = this->factoryCommands->create(command);
    this->commands[command] = exCommand;
    return exCommand;
}