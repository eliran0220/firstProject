//
// Created by afik on 12/15/18.
//

#ifndef FIRSTPROJECT_COMMANDEXPRESSION_H
#define FIRSTPROJECT_COMMANDEXPRESSION_H

#include "Expression.h"
#include "../Commands/Command.h"

class CommandExpression : public Expression {

private:
    Command* command;
    vector<string>* parameters;
    int position;


public:
    CommandExpression(Command* c) {
        this->command = c;
    }
    virtual double calculate(){
        return command->execute(*this->parameters, position);
    }
    virtual void setLexerStringAndPosition(vector<string>* parameters, int position) {
        this->position = position;
        this->parameters = parameters;
    }
    virtual ~CommandExpression() {
        delete(command);
    }

};

#endif //FIRSTPROJECT_COMMANDEXPRESSION_H
