//
// Created by afik on 12/16/18.
//

#ifndef FIRSTPROJECT_FACTORYCOMMANDS_H
#define FIRSTPROJECT_FACTORYCOMMANDS_H

#include <string>

#include "../Useful/SymbolTable.h"
#include "../Commands/SleepCommand.h"
#include "../Expressions/CommandExpression.h"
#include "../Commands/PrintCommand.h"
#include "../Commands/DefineVarCommand.h"
#include "../Useful/Factory.h"

using namespace std;

#define PRINT_COMMAND  "print"
#define SLEEP_COMMAND  "sleep"
#define DEFINE_VAR_COMMAND "var"
#define DEFINE_INITIALIZE_COMMAND "="

class FactoryCommands: public Factory {

private:
    Factory* createExpression;
    SymbolTable* symbolTable;
public:
    FactoryCommands();

    ~FactoryCommands();

    virtual Expression* create(const string &command);

};
#endif //FIRSTPROJECT_FACTORYCOMMANDS_H
