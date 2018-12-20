//
// Created by afik on 12/15/18.
//


#include <iostream>
#include "FactoryExpression.h"


FactoryExpression::~FactoryExpression() {

}
vector<string> FactoryExpression::splitExpression(string stringExpression) {
    vector<string> split;
    string temp;
    string stringNumber;
    regex letterR("[a-zA-Z]");
    regex numberR("[0-9]");
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
        }
        if (temp != " ") {
            split.push_back(temp);
        }
    }
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

vector<string> shuntingYardAlgorithm(vector<string> strings) {
    vector<string> prefix = strings;
    vector<string> infix;
    string temp;
    regex varR("[a-zA-Z0-9]+");
    regex numberR("[0-9]+||[0-9].{0,1}[0-9]+");
    regex operatorR("[+]||[-]||[/]||[*]");
    stack<string> s;
    queue<string> q;
    for (int i = 0; i < prefix.size(); ++i) {
        if (regex_match(prefix[i], numberR) || regex_match(prefix[i], varR)) {
            q.push(prefix[i]);
        } else if (regex_match(prefix[i], operatorR)) {
            while ((! s.empty()) && regex_match(s.top(), operatorR)
                  && precedence(s.top()) >= precedence(prefix[i])) {
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

Expression* FactoryExpression::createExpressionFromStrings(vector<string> strings) {
    regex numberR("[0-9]+||[0-9].{0,1}[0-9]+");
    regex operatorR("[+]||[-]||[/]||[*]");
    regex varR("[a-zA-Z0-9]+");
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
            if (this->symbolTable->existsVariable(strings[i])) {
                tempEx = new Number(this->symbolTable->getSymbolTableValue(strings[i]));
            } else {
                // שיחרור הזיכרון לפני זריקת האקספשיין
                Expression* tempFree;
                while (!stackEx.empty()) {
                    tempFree = stackEx.top();
                    stackEx.pop();
                    delete (tempFree);
                }
                throw "The variable doesn't exist factoryCreate failed";
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

Expression* FactoryExpression::create(const string &exString) {
    vector<string> splitEx;
    splitEx = splitExpression(exString);
    splitEx = shuntingYardAlgorithm(splitEx);
    return createExpressionFromStrings(splitEx);
}