//
// Created by afik on 12/13/18.
//




#include "RunTheSimulator.h"

vector<string> splitCommand(string &givenLine);

vector<string> splitVarCommand(string &givenLine);

vector<string>
splitLineCommandCondition(string &givenLine, string command);

vector<string>
splitLineWithOneArguments(string &givenLine, string command);

vector<string>
splitLineWithTwoArguments(string &givenLine, string command);

vector<string> splitInitializationOperator(string &givenLine);

void eraseBrackets(vector<string> *strings, int indication, int endOfCheck);

bool checkPrefix(string fullString, string prefix);


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


vector<string> splitCommand(string &givenLine) {
    vector<string> vec;
    if (checkPrefix(givenLine, "var")) {
        return splitVarCommand(givenLine);
    }
    if (checkPrefix(givenLine, "while")) {
        return splitLineCommandCondition(givenLine, "while");
    }
    if (checkPrefix(givenLine, "if")) {
        return splitLineCommandCondition(givenLine, "if");
    }
    if (checkPrefix(givenLine, "openDataServer")) {
        return splitLineWithTwoArguments(givenLine, "openDataServer");
    }
    if (checkPrefix(givenLine, "connect")) {
        return splitLineWithTwoArguments(givenLine, "connect");
    }
    if (checkPrefix(givenLine, "sleep")) {
        return splitLineWithOneArguments(givenLine, "sleep");
    }
    if (checkPrefix(givenLine, "print")) {
        return splitLineWithOneArguments(givenLine, "print");
    }
    if (checkPrefix(givenLine, "=")) {
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
splitLineCommandCondition(string &givenLine, string command) {
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

vector<string> splitVarCommand(string &givenLine) {
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
splitLineWithTwoArguments(string &givenLine, string command) {
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
        regex operatorR("[+]||[-]||[/]||[*]");
        vector<string> tempVector;
        string tempString;
        char prev;
        bool flagCurrentIndex;
        bool flagTopVector;
        bool flagTabOrSpace;
        bool stopToSeparate = false;
        for (int i = 0; i < tempSubString.size(); ++i) {
            tempString = tempSubString[i];
            flagTabOrSpace = (tempSubString[i] == ' ' || tempSubString[i] == '\t');
            if (!flagTabOrSpace) {
                flagCurrentIndex = regex_match(tempString.c_str(), operatorR);
                flagTopVector = (!tempVector.empty()) && !(regex_match(tempVector[tempVector.size() - 1], operatorR));
                if ((!flagCurrentIndex) && flagTopVector && (!stopToSeparate)) {
                    if (prev == ' ' || prev == '\t') {
                        tempVector.push_back("&");
                        tempVector.push_back(tempString);
                        stopToSeparate = true;
                    } else {
                        tempVector.push_back(tempString);
                    }
                } else {
                    tempString = tempSubString[i];
                    tempVector.push_back(tempString);
                }
            }
            prev = tempSubString[i];
        }
        tempString = "";
        for (int j = 0; j < tempVector.size(); ++j) {
            if (tempVector[j] != "&") {
                tempString += tempVector[j];
            } else {
                vec.push_back(tempString);
                tempString = "";
            }
        }
        if (tempString != "") {
            vec.push_back(tempString);
        }
    }
    if (vec.size() == NO_ARGUMENTS && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error no arguments";
    }
    if (vec.size() > TWO_ARGUMENTS && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error to much arguments";
    }
    if (vec.size() == OME_ARGUMENTS && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error Separate with char ',' ";
    }
    eraseBrackets(&vec, END_LINE, 0);
    return vec;
}

vector<string>
splitLineWithOneArguments(string &givenLine, string command) {
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

vector<string> splitInitializationOperator(string &givenLine) {
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

bool checkPrefix(string fullString, string prefix) {
    int counter = 0;
    for (int i = 0; i < fullString.size(); ++i) {
        if (counter == prefix.size()) {
            return true;
        }
        if (fullString[i] != ' ' && fullString[i] != '\t') {
            if (fullString[i] != prefix[counter]) {
                return false;
            } else {
                counter++;
            }
        }
    }
    return false;
}