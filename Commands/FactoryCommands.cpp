//
// Created by afik on 12/16/18.
//

#include "FactoryCommands.h"


FactoryCommands::FactoryCommands() {
    this->symbolTable = new SymbolTable();
    this->castStringToExpression = new CastStringToExpression(this->symbolTable);
}

FactoryCommands::~FactoryCommands() {
    delete (this->symbolTable);
    delete(this->castStringToExpression);
}

Expression* FactoryCommands::createCommandExpression(string command) {
    if (command == SLEEP_COMMAND) {
        SleepCommand* sleepCommand = new SleepCommand(this->castStringToExpression);
        Expression* expressionCommand = new CommandExpression(sleepCommand);
        return  expressionCommand;
    }
    if (command == PRINT_COMMAND) {
        PrintCommand* printCommand = new PrintCommand(this->castStringToExpression);
        Expression* expressionCommand = new CommandExpression(printCommand);
        return  expressionCommand;
    }

    if (command == DEFINE_VAR_COMMAND){
        DefineVarCommand* defineVarCommand = new DefineVarCommand(symbolTable);
        Expression* expressionCommand = new CommandExpression(defineVarCommand);
        return expressionCommand;
    }

}



