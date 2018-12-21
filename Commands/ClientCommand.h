//
// Created by afik on 12/22/18.
//

#ifndef FIRSTPROJECT_CLIENTCOMMAND_H
#define FIRSTPROJECT_CLIENTCOMMAND_H

#include <regex>
#include <thread>
#include "Command.h"
#include "../Useful/SymbolTable.h"
#include "../Useful/Factory.h"
#include "../ServerAndClient/DataReaderClient.h"

class ClientCommand : public Command{
    SymbolTable* symbolTable;
    Factory* factoryExpression;
    bool shouldStop;
public:
    ClientCommand(SymbolTable* symbolTable, Factory* factoryExpression);
    ~ClientCommand();
    virtual int execute(vector<string> &parameters, int position);
};


#endif //FIRSTPROJECT_CLIENTCOMMAND_H
