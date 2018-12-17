//
// Created by afik on 12/16/18.
//

#ifndef FIRSTPROJECT_FACTORYCOMMANDS_H
#define FIRSTPROJECT_FACTORYCOMMANDS_H

#include <string>

#include "../Useful/SymbolTable.h"
#include "../Useful/CastStringToExpression.h"
#include "../Commands/SleepCommand.h"
#include "../Expressions/CommandExpression.h"
#include "../Commands/PrintCommand.h"
#include "../Commands/DefineVarCommand.h"

using namespace std;

#define PRINT_COMMAND  "print"
#define SLEEP_COMMAND  "sleep"
#define DEFINE_VAR_COMMAND "var"

class FactoryCommands {

private:
    CastStringToExpression* castStringToExpression;
    SymbolTable* symbolTable;
public:
    FactoryCommands();

    ~FactoryCommands();

    Expression* createCommandExpression(string command);

};
#endif //FIRSTPROJECT_FACTORYCOMMANDS_H
