#ifndef FACTORYCOMMANDS_H
#define FACTORYCOMMANDS_H

#include <string>
#include "InitializeCommand.h"
#include "IncreaseCounterCommand.h"
#include "ConditionParser.h"
#include "WhileCommmand.h"
#include "IfCommand.h"
#include "../Useful/SymbolTable.h"
#include "../Commands/SleepCommand.h"
#include "../Expressions/CommandExpression.h"
#include "../Commands/PrintCommand.h"
#include "../Commands/DefineVarCommand.h"
#include "../Useful/Factory.h"
#include "OpenServerCommand.h"
#include "ClientCommand.h"
#include "EntercCommand.h"


#define PRINT_COMMAND  "print"
#define SLEEP_COMMAND  "sleep"
#define DEFINE_VAR_COMMAND "var"
#define DEFINE_INITIALIZE_COMMAND "="
#define WHILE_COMMAND  "while"
#define IF_COMMAND "if"
#define OPEN_SERVER_COMMAND "openDataServer"
#define CLIENT_COMMAND "connect"
#define ENTERC "Enterc"

using namespace std;

class FactoryCommands : public Factory {

private:
    Factory *createExpression;
    SymbolTable *symbolTable;
public:
    FactoryCommands();

    ~FactoryCommands();

    virtual Expression *create(const string &command);

};

#endif
