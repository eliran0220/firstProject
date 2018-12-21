//
// Created by afik on 12/16/18.
//

#include "FactoryCommands.h"
#include "OpenServerCommand.h"
#include "ClientCommand.h"

FactoryCommands::FactoryCommands() {
    this->symbolTable = new SymbolTable();
    this->createExpression = new FactoryExpression(this->symbolTable);
}

FactoryCommands::~FactoryCommands() {
    delete (this->symbolTable);
    delete (this->createExpression);
}

Expression *FactoryCommands::create(const string &exString) {
    if (exString == SLEEP_COMMAND) {
        SleepCommand *sleepCommand = new SleepCommand(this->createExpression);
        Expression *expressionCommand = new CommandExpression(sleepCommand);
        return expressionCommand;
    }
    if (exString == PRINT_COMMAND) {
        PrintCommand *printCommand = new PrintCommand(this->createExpression);
        Expression *expressionCommand = new CommandExpression(printCommand);
        return expressionCommand;
    }

    if (exString == DEFINE_VAR_COMMAND) {
        DefineVarCommand *defineVarCommand = new DefineVarCommand(symbolTable);
        Expression *expressionCommand = new CommandExpression(defineVarCommand);
        return expressionCommand;
    }
    if (exString == DEFINE_INITIALIZE_COMMAND) {
        InitializeCommand *initializeCommand = new InitializeCommand(
                this->createExpression, symbolTable);
        Expression *expressionCommand = new CommandExpression(
                initializeCommand);
        return expressionCommand;
        // בדיקה האם זה משתנה שלא קיים כלומר משתנה בלי var לפני
    }
    if (exString == WHILE_COMMAND) {
        ConditionParser *whileCommand = new WhileCommand(this,
                                                         this->createExpression);
        Expression *expressionCommand = new CommandExpression(whileCommand);
        return expressionCommand;
    }
    if (exString == IF_COMMAND) {
        ConditionParser *ifCommand = new IfCommand(this,
                                                   this->createExpression);
        Expression *expressionCommand = new CommandExpression(ifCommand);
        return expressionCommand;
    }
    if (exString == OPEN_SERVER_COMMAND) {
        OpenServerCommand *openServerCommand = new OpenServerCommand(
                this->createExpression, this->symbolTable);
        Expression *expressionCommand = new CommandExpression(
                openServerCommand);
        return expressionCommand;
    }
    if (exString == CLIENT_COMMAND) {
        ClientCommand *clientCommand = new ClientCommand(this->symbolTable,
                                                         this->createExpression);
        Expression *expressionCommand = new CommandExpression(clientCommand);
        return expressionCommand;
    }
    if (this->symbolTable->existsInValueTableMap(exString)) {
        IncreaseCounterCommand *increaseCounterCommand = new IncreaseCounterCommand();
        Expression *expressionCommand = new CommandExpression(
                increaseCounterCommand);
        return expressionCommand;
    } else {
        throw "the variable doesn't exist FactoryCommand failed";
    }

}



