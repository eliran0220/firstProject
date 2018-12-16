//
// Created by eliran on 12/15/18.
//

#include <iostream>
#include "PrintCommand.h"

PrintCommand::PrintCommand(CastStringToExpression *castStringToExpression){
    this->castStringToExpression = castStringToExpression;
}
int PrintCommand::execute(const vector<string> &parameters, int position) {
    cout << parameters[position + 1]<<endl;
    /*
    regex varR("[a-zA-Z0-9]+");
    if (regex_match(parameters[position + 1], varR)) {
        Expression* e = this->castStringToExpression->createExpression(parameters[position + 1]);
        double value = e->calculate();
        cout<< value<<endl;
        delete (e);
    } else {
        cout << parameters[position + 1]<<endl;
    }
     */
    return position + 2;
}