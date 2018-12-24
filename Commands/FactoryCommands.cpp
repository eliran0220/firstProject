#include "FactoryCommands.h"

/**
 * Function name: FactoryCommands
 * The function operation: Constructs a new FactoryCommands
 */

FactoryCommands::FactoryCommands() {
    this->symbolTable = new SymbolTable();
    this->createExpression = new FactoryExpression(this->symbolTable);
}

/**
 * Function name: ~FactoryCommands
 * The function operation: Destructs the FactoryCommands
 */

FactoryCommands::~FactoryCommands() {
    delete (this->symbolTable);
    delete (this->createExpression);
}

/**
 * Function name: create
 * The function operation: The function creates a new Command, given by the string, and returns it
 * We have 8 types of command : print, sleep, var , = , while, if, openDataServer and connect
 * if we don't have a match, we create a "new" command called increament, which just moves the
 * position on the lexer by 1 (example, if we are positioned on a variable, we need to move
 * to the actual command)
 * @param exString string
 * @return Expression*
 */
Expression *FactoryCommands::create(const string &exString) {
    //if exString == "sleep"
    if (exString == SLEEP_COMMAND) {
        SleepCommand *sleepCommand = new SleepCommand(this->createExpression);
        Expression *expressionCommand = new CommandExpression(sleepCommand);
        return expressionCommand;
    }
    //if exString == "print"
    if (exString == PRINT_COMMAND) {
        PrintCommand *printCommand = new PrintCommand(this->createExpression);
        Expression *expressionCommand = new CommandExpression(printCommand);
        return expressionCommand;
    }
    //if exString == "var"
    if (exString == DEFINE_VAR_COMMAND) {
        DefineVarCommand *defineVarCommand = new DefineVarCommand(symbolTable);
        Expression *expressionCommand = new CommandExpression(defineVarCommand);
        return expressionCommand;
    }
    //if exString == "="
    if (exString == DEFINE_INITIALIZE_COMMAND) {
        InitializeCommand *initializeCommand = new InitializeCommand(
                this->createExpression, symbolTable);
        Expression *expressionCommand = new CommandExpression(
                initializeCommand);
        return expressionCommand;
        // בדיקה האם זה משתנה שלא קיים כלומר משתנה בלי var לפני
    }
    //if exString == "while"
    if (exString == WHILE_COMMAND) {
        ConditionParser *whileCommand = new WhileCommand(this,
                                                         this->createExpression);
        Expression *expressionCommand = new CommandExpression(whileCommand);
        return expressionCommand;
    }
    //if exString == "if"
    if (exString == IF_COMMAND) {
        ConditionParser *ifCommand = new IfCommand(this,
                                                   this->createExpression);
        Expression *expressionCommand = new CommandExpression(ifCommand);
        return expressionCommand;
    }
    //if exString == "openServerCommand"
    if (exString == OPEN_SERVER_COMMAND) {
        OpenServerCommand *openServerCommand = new OpenServerCommand(
                this->createExpression, this->symbolTable);
        Expression *expressionCommand = new CommandExpression(
                openServerCommand);
        return expressionCommand;
    }
    //if exString == "connect"
    if (exString == CLIENT_COMMAND) {
        ClientCommand *clientCommand = new ClientCommand(this->symbolTable,
                                                         this->createExpression);
        Expression *expressionCommand = new CommandExpression(clientCommand);
        return expressionCommand;
    }
    /*
    if (exString == ENTERC) {
        EntercCommand *entrecCommand = new EntercCommand();
        Expression *expressionCommand = new CommandExpression(entrecCommand);
        return expressionCommand;
    }
     */
    if (exString == EXIT) {
        ExitCommand *exit = new ExitCommand();
        Expression *expressionCommand = new CommandExpression(exit);
        return expressionCommand;
    }
    //The case we don't find any command matched to the string.
    if (this->symbolTable->existsInValueTableMap(exString)) {
        IncreaseCounterCommand *increaseCounterCommand = new IncreaseCounterCommand();
        Expression *expressionCommand = new CommandExpression(
                increaseCounterCommand);
        return expressionCommand;
    } else {
        throw "the variable doesn't exist FactoryCommand failed";
    }

}



