#include "InitializeCommand.h"

/**
 * Function name: execute
 * The function operation: The function initializes the variable.
 * If the parameter after the "=" is bind, we need to initialize the destination
 * of the variable in the destination table,
 * else, we need to initialize the value of the variable in the symbol table
 * @param parameters vector<string>
 * @param position int
 * @return int
 */
int
InitializeCommand::execute(vector<string> &parameters, int position) {
    if (parameters[position + 1] == "bind") {
        string value = parameters[position + 2];
        if (strstr(value.c_str(), "\"")) {
            value.erase(std::remove(value.begin(), value.end(), '\"'),
                        value.end());
            this->table->updateSymbolTableDest(parameters[position - 1], value);
            // if the expression is type of x = bind y
        } else if (this->table->existsInValueTableMap(value)) {
            string dest = this->table->getSymbolTableDest(value);
            this->table->updateSymbolTableDest(parameters[position - 1], dest);
        }
        return AMOUNT_MOVEMENT + 1;
        // If the expression is type of x = (y or var)
    } else {
        Expression *e = this->expression->create(parameters[position + 1]);
        double value = e->calculate();
        this->table->updateSymbolTableValue(parameters[position - 1], value);
        delete (e);
        return AMOUNT_MOVEMENT;
    }
}

/**
 * Function name: InitializeCommand
 * The function operation: Constructs a new InitializeCommand
 * @param expression given expression
 * @param table given table
 */
InitializeCommand::InitializeCommand(Factory *expression,
                                     SymbolTable * &table) {
    this->expression = expression;
    this->table = table;
}
