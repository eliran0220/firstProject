//
// Created by afik on 12/15/18.
//


#include <iostream>
#include "FactoryExpression.h"

vector<string> splitExpression(string stringExpression) {
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
            while ((! s.empty()) && regex_match(s.top(), operatorR)) {
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
    Expression* tempEx;
    Expression* left;
    Expression* right;
    double tempNum;
    for (int i = 0; i < strings.size(); ++i) {
        if (regex_match(strings[i], numberR)) {
            tempNum = stod(strings[i].c_str());
            tempEx = new Number(tempNum);
            stackEx.push(tempEx);
        } else if (regex_match(strings[i], varR)){
            if (this->symbolTable->existsVariableValue(strings[i])) {
                tempEx = new Number(this->symbolTable->getValueSymbtolTable(strings[i]));
            } else {
                cout<<"The variable does not exists";
                // לשחרר את זיכרון שקיים במחסנית
                // להוסיף תנאי לכול קומפאנד שמקבל אקספרשיין שהוא שונה מnull
                return NULL;
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
    tempEx = stackEx.top();
    stackEx.pop();
    return tempEx;
}

Expression* FactoryExpression::create(const string &exString) {
    vector<string> splitEx;
    splitEx = splitExpression(exString);
    splitEx = shuntingYardAlgorithm(splitEx);
    return createExpressionFromStrings(splitEx);
    // לא לשכוח להוסיף לליסט של הביטויים של המחלקה בשביל שיחרורי הזיכרון
    // לממש דיסרקטור
}