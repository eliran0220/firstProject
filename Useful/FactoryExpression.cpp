//
// Created by afik on 12/15/18.
//


#include <iostream>
#include "FactoryExpression.h"


/**
 * Function name: splitExpression
 * The input: string
 * The output: vector<string>
 * The function operation: The function gets a string and splits it.
 *
 * @param stringExpression
 * @return
 */
vector<string> FactoryExpression::splitExpression(string stringExpression) {
    vector<string> split;
    string temp;
    string stringNumber;
    regex letterR("[a-zA-Z_]");
    regex numberR("[0-9]");
    regex operatorR("[+]||[-]||[/]||[*]");
    bool flag = false;
    for (int i = 0; i < stringExpression.size(); ++i) {
        temp = stringExpression[i];
        while (regex_match(temp, letterR) || regex_match(temp, numberR) || temp == ".") {
            stringNumber = stringNumber + temp;
            flag = true;
            i++;
            temp = stringExpression[i];
        }
        if (flag){
            split.push_back(stringNumber);
            stringNumber = "";
            flag = false;
            // תנאי אם קיים ביטוי שלילי
        } if ((temp == "-" || temp == "+") && !split.empty()) {
            if (regex_match(split[split.size() - 1], operatorR) || split[split.size() - 1] == "(") {
                split.push_back("0");
            }
            split.push_back(temp);
        } else if (temp != " ") {
            split.push_back(temp);
        }
    }
    //אולי צריך להוריד
    split.erase(std::remove(split.begin(),split.end(),""));
    return split;
}

int precedence(string& op){
    if(op == "+"||op == "-"){
        return 1;
    }
    if(op == "*" ||op == "/") {
        return 2;
    }
    return 0;
}

/**
 * Function name: shuntingYardAlgorithm
 * The input: vector<string>
 * The output: vector<string>
 * The function operation: The function gets a vector if strings, and applies the shunting yard
 * algorithm on the vector. We work by "regular expressions" so we check each time if we have
 * a match between the element in the vector to the item we defined in the function, and we operate
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
    for (int i = 0; i < prefix.size(); ++i) {
        //if we have a variable, or number
        if (regex_match(prefix[i], numberR) || regex_match(prefix[i], varR)) {
            //push to the queue
            q.push(prefix[i]);
            //if we have an operator
        } else if (regex_match(prefix[i], operatorR)) {
            //while the stack isn't empty
            while ((! s.empty()) && regex_match(s.top(), operatorR)
                  && precedence(s.top()) >= precedence(prefix[i])) {
                //push to stack by priority
                q.push(s.top());
                s.pop();
            }
            s.push(prefix[i]);
        } else if (prefix[i] == "(") {
            s.push(prefix[i]);
        } else if (prefix[i] == ")") {
            while (! s.empty()) {
                if ( s.top() != "(") {
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
    while (! s.empty()) {
        q.push(s.top());
        s.pop();
    }
    while (!q.empty()) {
        temp = q.front();
        infix.push_back(temp);
        q.pop();
    }
    return infix;
}

/**
 * Function name: createExpressionFromString
 * The input: vector<string>
 * The output: Expression
 * The function operation: The function gets a vector of strings, and creates an expression from it.
 *
 * @param strings
 * @return
 */
Expression* FactoryExpression::createExpressionFromStrings(vector<string> strings) {
    regex numberR("[0-9]+||[0-9].{0,1}[0-9]+");
    regex operatorR("[+]||[-]||[/]||[*]");
    regex varR("[a-zA-Z0-9_]+");
    stack<Expression*> stackEx;
    Expression* tempEx = nullptr;
    Expression* left;
    Expression* right;
    double tempNum;
    for (int i = 0; i < strings.size(); ++i) {
        if (regex_match(strings[i], numberR)) {
            tempNum = stod(strings[i].c_str());
            tempEx = new Number(tempNum);
            stackEx.push(tempEx);
        } else if (regex_match(strings[i], varR)){
            // check if the variable in the symbol table
            if (this->symbolTable->existsInValueTableMap(strings[i])) {
                tempEx = new Number(this->symbolTable->getSymbolTableValue(strings[i]));
                stackEx.push(tempEx);
            } else {
                // שיחרור הזיכרון לפני זריקת האקספשיין
                Expression* tempFree;
                while (!stackEx.empty()) {
                    tempFree = stackEx.top();
                    stackEx.pop();
                    delete (tempFree);
                }
                throw "The variable doesn't exist factoryCreateExpression failed";
            }
        } else {
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
            }  else if (strings[i] == "-") {
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
 * The input: string
 * The output: Expression
 * The function operation: The function creates an expression from a given string, using all the functions
 * above.
 * @param exString a given string
 * @return Expression*
 */
Expression* FactoryExpression::create(const string &exString) {
    vector<string> splitEx;
    splitEx = splitExpression(exString);
    splitEx = shuntingYardAlgorithm(splitEx);
    return createExpressionFromStrings(splitEx);
}