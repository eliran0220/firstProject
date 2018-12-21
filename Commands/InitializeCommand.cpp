//
// Created by eliran on 12/17/18.
//

#include "InitializeCommand.h"
#include <algorithm>
#include <cstring>

int
InitializeCommand::execute(vector<string> &parameters, int position) {
    if (parameters[position + 1] == "bind") {
        string value = parameters[position + 2];
        if (strstr(value.c_str(),"\"")) {
            this->table->updateSymbolTableDest(parameters[position-1],value);
            // אם נקבל ביטוי מהצורה var x = bind y
        } else if (this->table->existsInValueTableMap(value)) {
            string dest = this->table->getSymbolTableDest(value);
            this->table->updateSymbolTableDest(parameters[position - 1], dest);
        }
        return 3;
    } else {
        Expression *e = this->expression->create(parameters[position+1]);
        this->table->updateSymbolTableValue(parameters[position - 1], e->calculate());
        return 2;
    }
}

InitializeCommand::InitializeCommand(Factory *expression,
                                     SymbolTable *table) {
    this->expression = expression;
    this->table = table;
}
