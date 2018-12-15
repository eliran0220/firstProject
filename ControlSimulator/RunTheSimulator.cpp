//
// Created by afik on 12/13/18.
//




#include <regex>
#include <queue>
#include "RunTheSimulator.h"
#include "../Expressions/Div.h"
#include "../Expressions/Mult.h"
#include "../Expressions/Plus.h"
#include "../Expressions/Minus.h"
#include "../Expressions/Number.h"


bool checkIfLineIsConditionCommand(const string &givenLine);
vector<string> splitExpression(string stringExpression);
vector<string> ShuntingYardAlgorithm(vector<string> strings);
Expression* createExpressionFromStrings(vector<string> strings, int position);

void RunTheSimulator::parser(string fileName){
    fstream file(fileName);
    if (!file) {
        cout << "file does not exists";
        return;
    }
    vector<string> command = lexer(file);
    vector<string> splitCom;
    while (!command.empty()) {
        command = lexer(file);
        for (int i = 0; i < command.size(); ++i) {
            splitCom = splitCommand(command[i]);
        }
    }
    file.close();
}

vector<string> RunTheSimulator::lexer(fstream &file) {
    vector<string> command;
    string line;
    bool check;
    if (!file.eof()) {
        getline(file, line);
        check = checkIfLineIsConditionCommand(line);
        if (check) {
            command = ReadConditionBLock(file, line);
        } else {
            command.push_back(line);
        }
    }
    return command;
}

vector<string> RunTheSimulator::splitCommand(const string &givenLine) {
    vector<string> vec;
    stringstream ss(givenLine);
    string item;
    getline(ss, item, ' ');
    while (getline(ss, item, ' ')) {
        if (strcmp(item.c_str(), "") == EQUAL ) {
            continue;
        } else if (strcmp(item.c_str(), "=") == EQUAL) {
            getline(ss, item);
            if (strstr(item.c_str(), "bind")) {
                stringstream temp(item);
                getline(temp, item, ' ');
                vec.push_back(item);
                getline(temp, item, ' ');
                item.erase(std::remove(item.begin(), item.end(), '"'), item.end());
                vec.push_back(item);
            } else {
                vec.push_back(item);
            }
        } else if (strstr(item.c_str(), "{") && !strstr(item.c_str(), " ")) {
            stringstream temp(item);
            getline(temp, item, '{');
            vec.push_back(item);
            getline(ss, item);
            vec.push_back(item);
        } else {
            item.erase(std::remove(item.begin(), item.end(), '"'), item.end());
            vec.push_back(item);
        }
    }
    return vec;
}

/*
* Prototype algorithem for conditions:
* check if a line contains a condition
* if we see a line which contains "if,while,for" we do the split
* command function, and repeat the algorithem untill we see }
* than, we add } to the vector.
*/
vector<string>
RunTheSimulator::ReadConditionBLock(fstream &file,
                                  const string &firstLineBlock) {
    vector<string> command;
    string line;
    int amountBlock = 1;
    int counter = 0;
    command.push_back(firstLineBlock);
    while (counter < amountBlock) {
        getline(file, line);
        command.push_back(line);
        if (strstr(line.c_str(), "{")) {
            amountBlock++;
        } else if (strstr(line.c_str(), "}")) {
            counter++;
        }
    }
    return command;
}

bool checkIfLineIsConditionCommand(const string &givenLine) {

    return strstr(givenLine.c_str(), WHILE_LOOP) ||
           strstr(givenLine.c_str(), FOR_LOOP)
           || strstr(givenLine.c_str(), IF);

}

vector<string> RunTheSimulator::splitExpression(string stringExpression) {
    vector<string> split;
    string temp;
    string stringNumber;
    regex letterR("[a-zA-Z]");
    regex numberR("[0-9]");
    bool flag = false;
    for (int i = 0; i < stringExpression.size(); ++i) {
        temp = stringExpression[i];
        while (regex_match(temp, letterR) || regex_match(temp, numberR)) {
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


vector<string> RunTheSimulator::ShuntingYardAlgorithm(vector<string> strings) {
    vector<string> prefix = strings;
    vector<string> infix;
    string temp;
    regex varR("[a-zA-Z0-9]+");
    regex numberR("[0-9]+");
    regex operatorR("[+]||[-]||[/]||[*]");
    stack<string> s;
    queue<string> q;
    for (int i = 0; i < prefix.size(); ++i) {
        if (regex_match(prefix[i], numberR)) {
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

Expression* RunTheSimulator::createExpressionFromStrings(vector<string> strings, int position) {
    regex numberR("[0-9]+");
    regex operatorR("[+]||[-]||[/]||[*]");
    if (position == 0) {
        double number = atoi(strings[position].c_str());
        return new Number(number);
    }
    // תנאי אם אחד הביטויים הוא משתנה שצריך למשוך
    Expression* left;
    Expression* right = createExpressionFromStrings(strings, position - 1);
    if (regex_match(strings[position - 1], operatorR)) {
        left = createExpressionFromStrings(strings, position - 4);
    } else {
        left = createExpressionFromStrings(strings, position - 2);
    }
    if (regex_match(strings[position], numberR)) {
        double number = atoi(strings[position].c_str());
        return new Number(number);
    }
    // תנאי אם אחד הביטויים הוא משתנה שצריך למשוך
    if (strings[position] == "/") {
        return new Div(left, right);
    }
    if (strings[position] == "*") {
        return new Mult(left, right);
    }
    if (strings[position] == "+") {
        return new Plus(left, right);
    }
    if (strings[position] == "-") {
        return new Minus(left, right);
    }
}