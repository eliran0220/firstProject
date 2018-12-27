#include "FactoryExpression.h"

string decorateBrackets(string stringToDecorate, int start);

/**
 * Function name: splitExpression
 * The function operation: The function gets a string and splits it.
 * @param stringExpression given string
 * @return vector<string>
 */
vector<string> FactoryExpression::splitExpression(string stringExpression) {
    vector<string> split;
    string temp;
    string stringNumber;
    regex letterR("[a-zA-Z_]");
    regex numberR("[0-9]");
    regex operatorR("[+]||[-]||[/]||[*]");
    bool flag = false;
    // check if the first number is negative if is add 0
    if (stringExpression[0] == '-' || stringExpression[0] == '+') {
        split.push_back("0");
    }
    for (int i = 0; i < (int)stringExpression.size(); ++i) {
        temp = stringExpression[i];
        while (regex_match(temp, letterR) || regex_match(temp, numberR) ||
               temp == ".") {
            stringNumber = stringNumber + temp;
            flag = true;
            i++;
            temp = stringExpression[i];
        }
        if (flag) {
            split.push_back(stringNumber);
            stringNumber = "";
            flag = false;
        }
        // check if temp is an operator - or  +.
        if ((temp == "-" || temp == "+") && !split.empty()) {
            // check if the last string is an operator
            if (regex_match(split[split.size() - 1], operatorR)) {
                split.push_back("(");
                split.push_back("0");
                // decorate the expression with brackets
                stringExpression = decorateBrackets(stringExpression, i + 1);
            } else if (split[split.size() - 1] == "(") {
                split.push_back("0");
            }
            split.push_back(temp);
        } else if (temp != "" || temp != "=") {
            split.push_back(temp);
        }
    }
    return split;
}

/**
 * Function name: precedence
 * The function operation: The function sorts the priority of the operators.
 * @param op
 * @return int
 */
int precedence(string &op) {
    if (op == "+" || op == "-") {
        return 1;
    }
    if (op == "*" || op == "/") {
        return 2;
    }
    return 0;
}

/**
 * Function name: decorateBrackets
 * The function operation: The function decorates the expression with brackets.
 * @param stringToDecorate
 * @param start
 * @return
 */
string decorateBrackets(string stringToDecorate, int start) {
    int counter = 0;
    int amountBrackets = 0;
    string s;
    regex letter("[0-9a-zA-Z_]");
    // count the first bracket
    if (start < (int)stringToDecorate.size() && stringToDecorate[start] == '(') {
        amountBrackets = 1;
    }
    // concatenate the string
    for (int i = 0; i < start; ++i) {
        s += stringToDecorate[i];
    }
    // find the end expression to decorate.
    while (counter < amountBrackets && start < (int)stringToDecorate.size()) {
        if (stringToDecorate[start] == '(') {
            amountBrackets++;
        }
        if (stringToDecorate[start] == ')') {
            counter++;
        }
        s += stringToDecorate[start];
        start++;
    }
    // if the expression not have brackets
    while (amountBrackets == 0 && start < (int)stringToDecorate.size()) {
        string temp;
        temp += stringToDecorate[start];
        if (!regex_match(temp.c_str(), letter)) {
            start--;
            break;
        }
        s += stringToDecorate[start];
        start++;
    }
    s += ')';
    // concatenate the end string
    for (int j = start; j < (int)stringToDecorate.size(); ++j) {
        s += stringToDecorate[j];
    }
    return s;
}

/**
 * Function name: shuntingYardAlgorithm
 * The function operation: The function gets a vector if strings, and applies
 * the shunting yard algorithm on the vector. We work by "regular expressions"
 * so we check each time if we have a match between the element in the vector
 * to the item we defined in the function, and we operate
 * by the shunting yard algorithm, untill we have no elements.
 * @param strings vector of strings
 * @return vector<string>
 */
vector<string> shuntingYardAlgorithm(vector<string> strings) {
    vector<string> prefix = strings;
    vector<string> infix;
    string temp;
    regex varR("[a-zA-Z0-9_]+");
    regex numberR("[0-9]+||[0-9].{0,1}[0-9]+");
    regex operatorR("[+]||[-]||[/]||[*]");
    stack<string> s;
    queue<string> q;
    //iterate through the vector
    for (int i = 0; i < (int)prefix.size(); ++i) {
        //if we have a variable, or number
        if (regex_match(prefix[i], numberR) || regex_match(prefix[i], varR)) {
            //push to the queue
            q.push(prefix[i]);
            //if we have an operator
        } else if (regex_match(prefix[i], operatorR)) {
            //while the stack isn't empty
            while ((!s.empty()) && regex_match(s.top(), operatorR)
                   && precedence(s.top()) >= precedence(prefix[i])) {
                //push to stack by priority
                q.push(s.top());
                s.pop();
            }
            s.push(prefix[i]);
        } else if (prefix[i] == "(") {
            s.push(prefix[i]);
        } else if (prefix[i] == ")") {
            while (!s.empty()) {
                if (s.top() != "(") {
                    temp = s.top();
                    q.push(temp);
                    s.pop();
                } else {
                    s.pop();
                    break;
                }
            }
        }
    }
    //while stack isn't empty, push to queue, extract from stack
    while (!s.empty()) {
        q.push(s.top());
        s.pop();
    }
    //while queue isn't empty, exctract from queue, push to infix, do again
    while (!q.empty()) {
        temp = q.front();
        infix.push_back(temp);
        q.pop();
    }
    return infix;
}

/**
 * Function name: createExpressionFromString
 * The function operation: The function gets a vector of strings, and creates
 * an expression from it.
 * @param strings given vector of strings
 * @return Expression*
 */
Expression *
FactoryExpression::createExpressionFromStrings(vector<string> strings) {
    regex numberR("[0-9]+||[0-9].{0,1}[0-9]+");
    regex operatorR("[+]||[-]||[/]||[*]");
    regex varR("[a-zA-Z0-9_]+");
    stack<Expression *> stackEx;
    Expression *tempEx = nullptr;
    Expression *left;
    Expression *right;
    double tempNum;
    for (int i = 0; i < (int)strings.size(); ++i) {
        if (regex_match(strings[i], numberR)) {
            tempNum = stod(strings[i].c_str());
            tempEx = new Number(tempNum);
            stackEx.push(tempEx);
        // check if the string is variables
        } else if (regex_match(strings[i], varR)) {
            // check if the variable in the symbol table
            if (this->symbolTable->existsInValueTableMap(strings[i])) {
                tempEx = new Number(
                        this->symbolTable->getSymbolTableValue(strings[i]));
                stackEx.push(tempEx);
            } else {
                // Release memory before throwing exception
                Expression *tempFree;
                while (!stackEx.empty()) {
                    tempFree = stackEx.top();
                    stackEx.pop();
                    delete (tempFree);
                }
                throw "The variable doesn't exist factoryExpression failed";
            }
            // else the string is an operator.
        } else {
            if (stackEx.size() < 2) {
                throw "Something wrong with the expression syntax";
            }
            right = stackEx.top();
            stackEx.pop();
            left = stackEx.top();
            stackEx.pop();
            if (strings[i] == "/") {
                tempEx = new Div(left, right);
            } else if (strings[i] == "*") {
                tempEx = new Mult(left, right);
            } else if (strings[i] == "+") {
                tempEx = new Plus(left, right);
            } else if (strings[i] == "-") {
                tempEx = new Minus(left, right);
            }
            stackEx.push(tempEx);
        }
    }
    if (!stackEx.empty()) {
        tempEx = stackEx.top();
        stackEx.pop();
    }
    if (tempEx == nullptr) {
        throw "Something wrong with the expression syntax";
    }
    return tempEx;
}

/**
 * Function name: create
 * The function operation: The function creates an expression from a given
 * string, using all the functions
 * above.
 * @param exString a given string
 * @return Expression*
 */
Expression *FactoryExpression::create(const string &exString) {
    vector<string> splitEx;
    splitEx = splitExpression(exString);
    splitEx = shuntingYardAlgorithm(splitEx);
    return createExpressionFromStrings(splitEx);
}