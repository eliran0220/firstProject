//
// Created by eliran on 12/17/18.
//


#include "DefineVarCommand.h"

/**
 * Function name: execute
 * The input: vector<string>, int
 * The output: none
 * The function operation: creates the string of the var, and then adds the var to the tables.
 * Then, we move 2 positions in the lexer
 * @param parameters vector<string>
 * @param position int
 * @return
 */
int DefineVarCommand::execute(vector<string> &parameters, int position) {
    string var = parameters[position + 1];
    this->table->addToTable(var);
    return 2;
}

/**
 * Function name: DefineVarCommand
 * The input: SymbolTable
 * The output: none
 * The function operation: Constructs a new ClientCommand
 * @param symbolTable symbolTable
 */
DefineVarCommand::DefineVarCommand(SymbolTable *symbolTable) {
    this->table = symbolTable;
}

