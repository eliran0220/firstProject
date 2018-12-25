#ifndef COMMANDEXPRESSION_H
#define COMMANDEXPRESSION_H

#include "Expression.h"
#include "../Commands/Command.h"

/**
 * CommandExpression class: The CommandExpression class is the object
 * adapter
 */
class CommandExpression : public Expression {

private:
    Command *command;
    vector<string> *parameters;
    int position;

public:
    /**
     * Function name: CommandExpression
     * The function operation: The function constructs a new CommandExpression
     * @param c given command
     */
    CommandExpression(Command *c) {
        this->command = c;
    }

    /**
     * Function name: calculate
     * The function operation: The function calls the execute func of the initialized command, with
     * the parameters and the position.
     * @return double
     */
    virtual double calculate() {
        return command->execute(*this->parameters, position);
    }

    /**
     * Function name: setLexerStringAndPosition
     * The function operation: The function initialized the parameters and the position given in the
     * parameters (represent where we are right now at the vector)
     * @param parameters vector<string>
     * @param position int
     */
    virtual void
    setLexerStringAndPosition(vector<string> *parameters, int position) {
        this->position = position;
        this->parameters = parameters;
    }

    /**
     * Function name: ~CommandExpression
     * The function operation: Destrucsts the CommandExpression
     */
    virtual ~CommandExpression() {
        delete (command);
    }

};

#endif
