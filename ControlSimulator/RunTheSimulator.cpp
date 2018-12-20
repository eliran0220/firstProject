//
// Created by afik on 12/13/18.
//




#include "RunTheSimulator.h"

vector<string> splitCommand(const string &givenLine);

vector<string> splitVarCommand(const string &givenLine);
vector<string> splitLineCommandCondition(const string &givenLine, string command);
vector<string> splitLineWithOneArguments(const string &givenLine, string command);
vector<string> splitLineWithTwoArguments(const string &givenLine, string command);
vector<string> splitInitializationOperator(const string &givenLine);

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
    string tempSubString = givenLine.substr(2, givenLine.size());
    stringstream ss(tempSubString);
    string item;
    getline(ss, item, ' ');
    getline(ss, item);
    if (item != "") {
        item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
        vec.push_back(item);
    }
    return vec;
}


vector<string> splitLineCommandCondition(const string &givenLine, string command) {
    vector<string> vec;
    string item;
    string tempSubString;
    int start = (int) givenLine.find(command);
    tempSubString = givenLine.substr(start + command.size(), givenLine.size());
    stringstream ss(tempSubString);
    vec.push_back(command);
    if (strstr(givenLine.c_str(), "{")) {
        getline(ss, item, '{');
        item.erase(std::remove(item.begin(), item.end(), ' '),
                   item.end());
        vec.push_back(item);
        vec.push_back("{");
        return vec;
    }
    getline(ss, item);
    item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
    vec.push_back(item);
    if ((vec.size() == MISSING_PARAMETER) && (vec.size() == TWO && vec[1] == "{")){
        throw "Syntax Error missing condition";
    }
    return vec;
}

vector<string> splitVarCommand(const string &givenLine) {
    vector<string> vec;
    string item;
    string tempSubString;
    int start = (int) givenLine.find("var");
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
    if (vec.size() == MISSING_PARAMETER) {
        throw "Syntax Error missing var statement";
    }
    return vec;
}

vector<string> splitLineWithTwoArguments(const string &givenLine, string command) {
    vector<string> vec;
    string item;
    string tempSubString;
    int start = (int) givenLine.find(command);
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
    if (vec.size() == NO_ARGUMENTS) {
        throw "Syntax Error no arguments";
    }
    if (vec.size() > TWO_ARGUMENTS) {
        throw "Syntax Error to much arguments";
    }
    if (vec.size() == OME_ARGUMENTS) {
        throw "Syntax Error missing one argument Separate with char ',' ";
    }
    return vec;
}

vector<string> splitLineWithOneArguments(const string &givenLine, string command) {
    vector<string> vec;
    string tempSubString;
    int start = (int) givenLine.find(command);
    tempSubString = givenLine.substr(start + command.size(), givenLine.size());
    stringstream ss(tempSubString);
    vec.push_back(command);
    tempSubString.erase(std::remove(tempSubString.begin(), tempSubString.end(), ' '), tempSubString.end());
    vec.push_back(tempSubString);
    if (vec.size() == NO_ARGUMENTS) {
        throw "Syntax Error no arguments";
    }
    if (vec.size() > OME_ARGUMENTS) {
        throw "Syntax Error to much arguments";
    }
    return vec;
}

vector<string> splitInitializationOperator(const string &givenLine) {
    vector<string> vec;
    string item;
    string tempSubString = givenLine.substr(2, givenLine.size());
    stringstream ss(tempSubString);
    getline(ss, item, '=');
    item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
    item.erase(std::remove(item.begin(), item.end(), '\t'), item.end());
    vec.push_back(item);
    vec.push_back("=");
    getline(ss, item, '=');
    item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
    vec.push_back(item);
    if (vec.size() == MISSING_PARAMETER) {
        throw "Syntax Error missing initialization value";
    }
    return vec;
}

