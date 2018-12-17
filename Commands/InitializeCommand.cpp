//
// Created by eliran on 12/17/18.
//

#include "InitializeCommand.h"
#include <algorithm>

int
InitializeCommand::execute(const vector<string> &parameters, int position) {
    if (parameters[position + 1] == "bind") {
        string value = parameters[position + 2];
        this->table->updateDestTable(parameters[position-1],value);
        return 3;
    } else {
        Expression *e = this->expression->create(parameters[position+1]);
        this->table->updateSymbtolTable(parameters[position - 1],
                                 e->calculate());
        return 2;
    }
}

InitializeCommand::InitializeCommand(Factory *expression,
                                     SymbolTable *table) {
    this->expression = expression;
    this->table = table;

}
