//
// Created by eliran on 12/15/18.
//

#include <iostream>
#include "PrintCommand.h"

PrintCommand::PrintCommand(Factory *createExpression){
    this->createExpression = createExpression;
}

int PrintCommand::execute(vector<string> &parameters, int position) {
    regex varR("[a-zA-Z0-9]+");
    if (regex_match(parameters[position + 1], varR)) {
        Expression* e = this->createExpression->create(parameters[position + 1]);
        double value = e->calculate();
        cout<< value<<endl;
        delete (e);
    } else {
        string item = parameters[position + 1];
        // מחיקה של הגרשיים מהמחרוזת
        item.erase(std::remove(item.begin(), item.end(), '"'), item.end());
        cout << item<<endl;
    }
    return 2;
}