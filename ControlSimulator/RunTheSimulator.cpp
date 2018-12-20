//
// Created by afik on 12/13/18.
//




#include "RunTheSimulator.h"

vector<string> splitCommand(const string &givenLine);

vector<string> splitVarCommand(const string &givenLine);

vector<string>
splitLineCommandCondition(const string &givenLine, string command);

vector<string>
splitLineWithOneArguments(const string &givenLine, string command);

vector<string>
splitLineWithTwoArguments(const string &givenLine, string command);

vector<string> splitInitializationOperator(const string &givenLine);

void eraseBrackets(vector<string> *strings, int indication, int endOfCheck);

RunTheSimulator::RunTheSimulator() {
    this->collectionCommands = new CollectionCommands();
}

RunTheSimulator::~RunTheSimulator() {
    delete (this->collectionCommands);
}


void RunTheSimulator::parser(vector<string> commands) {
    Expression *command;
    int i = 0;
    while (i < commands.size()) {
        // ומה עם כאשר יש var נגיד באות h? זה קורס !
        command = this->collectionCommands->getExpressionCommand(commands[i]);
        command->setLexerStringAndPosition(&commands, i);
        i += (int) command->calculate();
    }
}


vector<string> RunTheSimulator::lexer(string fileName) {
    fstream file(fileName);
    vector<string> commands;
    vector<string> temp;
    string line;
    bool check;
    if (!file) {
        cout << "file does not exists";
        return commands;
    }
    while (!file.eof()) {
        getline(file, line);
        if (line == "")
            continue;
        temp = splitCommand(line);
        commands.insert(commands.end(), temp.begin(), temp.end());
    }
    file.close();
    return commands;
}


vector<string> splitCommand(const string &givenLine) {
    vector<string> vec;
    if (strstr(givenLine.c_str(), "var")) {
        return splitVarCommand(givenLine);
    }
    if (strstr(givenLine.c_str(), "while")) {
        return splitLineCommandCondition(givenLine, "while");
    }
    if (strstr(givenLine.c_str(), "if")) {
        return splitLineCommandCondition(givenLine, "if");
    }
    if (strstr(givenLine.c_str(), "openDataServer")) {
        return splitLineWithTwoArguments(givenLine, "openDataServer");
    }
    if (strstr(givenLine.c_str(), "connect")) {
        return splitLineWithTwoArguments(givenLine, "connect");
    }
    if (strstr(givenLine.c_str(), "sleep")) {
        return splitLineWithOneArguments(givenLine, "sleep");
    }
    if (strstr(givenLine.c_str(), "print")) {
        return splitLineWithOneArguments(givenLine, "print");
    }
    if (strstr(givenLine.c_str(), "=")) {
        return splitInitializationOperator(givenLine);
    }
    stringstream ss(givenLine);
    string item;
    getline(ss, item, ' ');
    getline(ss, item);
    if (item != "") {
        item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
        vec.push_back(item);
    }
    return vec;
}


vector<string>
splitLineCommandCondition(const string &givenLine, string command) {
    vector<string> vec;
    string item;
    string tempSubString;
    int start = (int) givenLine.find(command);
    vec.push_back(givenLine);
    eraseBrackets(&vec, START_LINE, start);
    tempSubString = givenLine.substr(start + command.size(), givenLine.size());
    stringstream ss(tempSubString);
    vec.push_back(command);
    /*
    if (strstr(givenLine.c_str(), "{")) {
        getline(ss, item, '{');
        item.erase(std::remove(item.begin(), item.end(), ' '),
                   item.end());
        vec.push_back(item);
        vec.push_back("{");
        return vec;
    }
     */
    getline(ss, item);
    item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
    vec.push_back(item);
    //if ((vec.size() == MISSING_PARAMETER) && (vec.size() == TWO && vec[1] == "{")){
    if (vec.size() == MISSING_PARAMETER && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error missing condition";
    }
    eraseBrackets(&vec, END_LINE, 0);
    return vec;
}

vector<string> splitVarCommand(const string &givenLine) {
    vector<string> vec;
    string item;
    string tempSubString;
    int start = (int) givenLine.find("var");
    vec.push_back(givenLine);
    eraseBrackets(&vec, START_LINE, start);
    tempSubString = givenLine.substr(start + 3, givenLine.size());
    stringstream ss(tempSubString);
    vec.push_back("var");
    if (strstr(givenLine.c_str(), "=") && getline(ss, item, '=')) {
        item.erase(std::remove(item.begin(), item.end(), ' '),
                   item.end());
        vec.push_back(item);
        getline(ss, item, '=');
        vec.push_back("=");
        if (strstr(givenLine.c_str(), "bind")) {
            item.erase(std::remove(item.begin(), item.end(), ' '),
                       item.end());
            item = item.substr(4, item.size());
            vec.push_back("bind");
            vec.push_back(item);
        } else {
            item.erase(std::remove(item.begin(), item.end(), ' '),
                       item.end());
            vec.push_back(item);
        }
        return vec;
    }
    getline(ss, item);
    item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
    vec.push_back(item);
    if (vec.size() == MISSING_PARAMETER && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error missing var statement";
    }
    eraseBrackets(&vec, END_LINE, 0);
    return vec;
}

vector<string>
splitLineWithTwoArguments(const string &givenLine, string command) {
    vector<string> vec;
    string item;
    string tempSubString;
    int start = (int) givenLine.find(command);
    vec.push_back(givenLine);
    eraseBrackets(&vec, START_LINE, start);
    tempSubString = givenLine.substr(start + command.size(), givenLine.size());
    vec.push_back(command);
    if (strstr(tempSubString.c_str(), ",")) {
        stringstream ss(tempSubString);
        getline(ss, item, ',');
        item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
        vec.push_back(item);
        getline(ss, item, ',');
        item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
        vec.push_back(item);
    } else {
        FactoryExpression f = FactoryExpression(NULL);
        vector<string> vecTemp = f.splitExpression(tempSubString);
        vec.insert(vec.end(), vecTemp.begin(), vecTemp.end());

    }
    if (vec.size() == NO_ARGUMENTS && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error no arguments";
    }
    if (vec.size() > TWO_ARGUMENTS && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error to much arguments";
    }
    if (vec.size() == OME_ARGUMENTS && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error missing one argument Separate with char ',' ";
    }
    eraseBrackets(&vec, END_LINE, 0);
    return vec;
}

vector<string>
splitLineWithOneArguments(const string &givenLine, string command) {
    vector<string> vec;
    string tempSubString;
    int start = (int) givenLine.find(command);
    vec.push_back(givenLine);
    eraseBrackets(&vec, START_LINE, start);
    tempSubString = givenLine.substr(start + command.size(), givenLine.size());
    stringstream ss(tempSubString);
    vec.push_back(command);
    tempSubString.erase(
            std::remove(tempSubString.begin(), tempSubString.end(), ' '),
            tempSubString.end());
    vec.push_back(tempSubString);
    if (vec.size() == NO_ARGUMENTS && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error no arguments";
    }
    if (vec.size() > OME_ARGUMENTS && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error to much arguments";
    }
    eraseBrackets(&vec, END_LINE, 0);
    return vec;
}

vector<string> splitInitializationOperator(const string &givenLine) {
    vector<string> vec;
    string item;
    int start = (int) givenLine.find("=");
    vec.push_back(givenLine);
    eraseBrackets(&vec, START_LINE, start);
    stringstream ss(givenLine);
    getline(ss, item, '=');
    item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
    item.erase(std::remove(item.begin(), item.end(), '\t'), item.end());
    vec.push_back(item);
    vec.push_back("=");
    getline(ss, item, '=');
    item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
    vec.push_back(item);
    if (vec.size() == MISSING_PARAMETER && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error missing initialization value";
    }
    eraseBrackets(&vec, END_LINE, 0);
    return vec;
}

void eraseBrackets(vector<string> *strings, int indication, int endOfCheck) {
    string temp;
    if (indication == END_LINE) {
        string temp = strings->at(strings->size() - 1);
        if (strstr(temp.c_str(), "{")) {
            temp.erase(std::remove(temp.begin(), temp.end(), '{'), temp.end());
            strings->at(strings->size() - 1) = temp;
            strings->push_back("{");
        } else if (strstr(temp.c_str(), "}")) {
            temp.erase(std::remove(temp.begin(), temp.end(), '}'), temp.end());
            strings->at(strings->size() - 1) = temp;
            strings->push_back("}");
        }
    } else if (indication == START_LINE) {
        temp = strings->at(0);
        for (int i = 0; i < endOfCheck; ++i) {
            if (temp[i] == '{') {
                strings->at(0) = "{";
                return;
            }
            if (temp[i] == '}') {
                strings->at(0) = "}";
                return;
            }
        }
        // אם לא נמצא סוגרת פותח או סוגר סוג בתחילת השורה
        strings->pop_back();
    }
}