//
// Created by afik on 12/15/18.
//

#ifndef FIRSTPROJECT_COMMANDEXPRESSION_H
#define FIRSTPROJECT_COMMANDEXPRESSION_H

#include "Expression.h"
#include "../Commands/Command.h"

class CommandExpression : public Expression {

private:
    Command *command;
    vector<string> *parameters;
    int position;


public:
    /**
     * Function name: CommandExpression
     * The input: Command*
     * The output: none
     * The function operation: The function constructs a new CommandExpression
     * @param c given command
     */
    CommandExpression(Command *c) {
        this->command = c;
    }

    /**
     * Function name: calculate
     * The input: none
     * The output: double
     * The function operation: The function calls the execute func of the initialized command, with
     * the parameters and the position.
     * @return double
     */
    virtual double calculate() {
        return command->execute(*this->parameters, position);
    }

    /**
     * Function name: setLexerStringAndPosition
     * The input: vector<string>, int
     * The output: none
     * The function operation: The function initialized the parameters and the position given in the
     * parameters (represent where we are right now at the vector)
     * @param parameters vector<string>
     * @param position int
     */
    virtual void setLexerStringAndPosition(vector<string> *parameters, int position) {
        this->position = position;
        this->parameters = parameters;
    }

    /**
     * Function name: ~CommandExpression
     * The input: none
     * The output: none
     * The function operation: Destrucsts the CommandExpression
     */
    virtual ~CommandExpression() {
        delete (command);
    }

};

#endif //FIRSTPROJECT_COMMANDEXPRESSION_H
