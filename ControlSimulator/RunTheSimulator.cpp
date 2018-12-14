//
// Created by afik on 12/13/18.
//




#include <regex>
#include <queue>
#include "RunTheSimulator.h"


bool checkIfLineIsConditionCommand(const string &givenLine);
bool checkIfCharIsOperator(char c);
vector<string> splitExpression(string stringExpression);
vector<string> ShuntingYardAlgorithm(vector<string> prefix);

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

vector<string> splitExpression(string stringExpression) {
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

bool checkIfCharIsOperator(char c) {
    if (c == '+' || c == '*' || c == '/' || c == '-') {
        return true;
    }
    return false;
}

vector<string> ShuntingYardAlgorithm(vector<string> prefix) {
    vector<string> infix;
    string temp;
    regex varR("[a-zA-Z0-9]+");
    regex numberR("[0-9]+");
    regex operatorR("[+]||[-]||[/]||[*]");
    stack<string> s;
    queue<string> q;
    bool flagOperatorInStack = false;
    for (int i = 0; i < prefix.size(); ++i) {
        if (regex_match(prefix[i], numberR)) {
            q.push(prefix[i]);
        } else if (regex_match(prefix[i], operatorR)) {
            while ((! s.empty()) && regex_match(s.top(), operatorR)) {
                q.push(s.top());
                s.pop();
                flagOperatorInStack = true;
            }
            if (!flagOperatorInStack) {
                s.push(prefix[i]);
            }
            flagOperatorInStack = false;
        } else if (prefix[i] == "(") {
            s.push(prefix[i]);
        } else if (prefix[i] == ")") {
            while (! s.empty()) {
                if ( s.top() != "(") {
                    temp = s.top();
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
        infix.push_back(q.front());
        q.pop();
    }
    return infix;
}

void RunTheSimulator::check(string s) {
    vector<string> vec = splitExpression(s);
    vec = ShuntingYardAlgorithm(vec);
}