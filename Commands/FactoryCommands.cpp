//
// Created by afik on 12/16/18.
//

#include "FactoryCommands.h"
#include "InitializeCommand.h"


FactoryCommands::FactoryCommands() {
    this->symbolTable = new SymbolTable();
    this->createExpression = new FactoryExpression(this->symbolTable);
}

FactoryCommands::~FactoryCommands() {
    delete (this->symbolTable);
    delete(this->createExpression);
}

Expression* FactoryCommands::create(const string &exString) {
    if (exString == SLEEP_COMMAND) {
        SleepCommand* sleepCommand = new SleepCommand(this->createExpression);
        Expression* expressionCommand = new CommandExpression(sleepCommand);
        return  expressionCommand;
    }
    if (exString == PRINT_COMMAND) {
        PrintCommand* printCommand = new PrintCommand(this->createExpression);
        Expression* expressionCommand = new CommandExpression(printCommand);
        return  expressionCommand;
    }

    if (exString == DEFINE_VAR_COMMAND){
        DefineVarCommand* defineVarCommand = new DefineVarCommand(symbolTable);
        Expression* expressionCommand = new CommandExpression(defineVarCommand);
        return expressionCommand;
    }
    if (exString == DEFINE_INITIALIZE_COMMAND){
        InitializeCommand * initializeCommand = new InitializeCommand(this->createExpression, symbolTable);
        Expression* expressionCommand = new CommandExpression(initializeCommand);
        return expressionCommand;
    }

}



