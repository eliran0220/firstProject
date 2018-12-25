#include "PrintCommand.h"

/**
 * Function name: PrintCommand
 * The function operation: Constructs a new PrintCommand
 * @param createExpression given createExpression
 */
PrintCommand::PrintCommand(Factory *createExpression) {
    this->createExpression = createExpression;
}

/**
 * Function name: execute
 * The function operation: The function prints the next parameter in the lexer.
 * First we check if the next parameter is an expression we need to evaluate, if so , we do it and then print it
 * If not, it means it's a string, so we remove the ' " ' from it and print it.
 * Then, we return 2 to move the next command in the parser.
 * @param parameters vector<string>
 * @param position int
 * @return int
 */
int PrintCommand::execute(vector<string> &parameters, int position) {
    regex varR("[a-zA-Z0-9_]+");
    if (regex_match(parameters[position + 1], varR)) {
        Expression *e = this->createExpression->create(parameters[position + 1]);
        double value = e->calculate();
        cout << value << endl;
        delete (e);
    } else {
        string item = parameters[position + 1];
        //delete brackets from the string
        item.erase(std::remove(item.begin(), item.end(), '"'), item.end());
        cout << item << endl;
    }
    return AMOUNT_MOVEMENT;
}