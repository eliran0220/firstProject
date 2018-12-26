#include "RunTheSimulator.h"

/** Useful functions ***/
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

/**
 * Function name: RunTheSimulator
 * The function operation: Constructs a new RunTheSimulator
 */
RunTheSimulator::RunTheSimulator() {
    this->collectionCommands = new CollectionCommands();
}

/**
 * Function name: ~RunTheSimulator
 * The function operation: Destructs the RunTheSimulator
 */
RunTheSimulator::~RunTheSimulator() {
    delete (this->collectionCommands);
}

/**
 * Function name: parser
 * The function operation: The function goes through each command and
 * executes it. Everytime, we get the command expression from the collection,
 * set the lexer in the right position and call the calculate method,
 * which returns an int. We raise the i with the value of the int we got,
 * so we move to the next command to execute
 * by order in the vector given
 * @param commands
 */
void RunTheSimulator::parser(vector<string> commands) {
    Expression *command;
    int i = 0;
    int value;
    while (i < commands.size()) {
        command = this->collectionCommands->getExpressionCommand(commands[i]);
        command->setLexerStringAndPosition(&commands, i);
        value = (int) command->calculate();
        i += value;
        // check if the user input exit command.
        if (value == EXIT_VALUE) {
            break;
        }
    }
}

/**
 * Function name: lexer
 * The function operation: The function simply iterates thorugh everyline
 * in the given file,sends it to the slitCommand function, and inserts it
 * to a commands vector.In the end, when we iterated through all the lines in
 * the file, we close it and return the vector.
 * @param fileName the file path
 * @return the split vector
 */
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

/**
 * Function name: splitCommand
 * The function operation: The function gets a string, and splits it depends
 * on the prefix.
 * @param givenLine given string
 * @return vector<string>
 */
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
    if (strstr(givenLine.c_str(), "=")) {
        return splitInitializationOperator(givenLine);
    }
    // otherwise
    stringstream ss(givenLine);
    string item;
    getline(ss, item, ' ');
    getline(ss, item);
    item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
    if (item != "") {
        vec.push_back(item);
    }
    return vec;
}

/**
 * Function name: splitLineCommandCondition
 * The function operation: The function splits the string given the "while" or
 * "if" commands First we find the position where the command starts, then we
 * erase the brackets
 * @param givenLine
 * @param command
 * @return
 */
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
    getline(ss, item);
    item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
    vec.push_back(item);
    // check if the syntax is valid
    if (vec.size() == MISSING_PARAMETER && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error missing condition";
    }
    // split the brackets
    eraseBrackets(&vec, END_LINE, 0);
    return vec;
}


/**
 * Function name: splitVarCommand
 * The function operation: The function splits var command string.
 * @param givenLine
 * @return the split line
 */
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
    // check if the var have '=' operator
    if (strstr(givenLine.c_str(), "=") && getline(ss, item, '=')) {
        item.erase(std::remove(item.begin(), item.end(), ' '),
                   item.end());
        vec.push_back(item);
        getline(ss, item, '=');
        vec.push_back("=");
        // if the string have substring bind
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
    // split the brackets
    eraseBrackets(&vec, END_LINE, 0);
    return vec;
}

/**
 * Function name: splitLineWithTwoArguments
 * The function operation: The function splits function command string with
 * two arguments, check if the amount of variable is valid
 * (if not update the user to separate with ',') and erase
 * brackets by call the function eraseBrackets.
 * @param givenLine
 * @param command the function name
 * @return the split line
 */
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
    // if the user input separate char split by ','
    if (strstr(tempSubString.c_str(), ",")) {
        stringstream ss(tempSubString);
        getline(ss, item, ',');
        item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
        vec.push_back(item);
        getline(ss, item, ',');
        item.erase(std::remove(item.begin(), item.end(), ' '), item.end());
        vec.push_back(item);
    // else separate with ' '
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
            flagTabOrSpace = (tempSubString[i] == ' ' ||
                              tempSubString[i] == '\t');
            // if the current char is not a tab or space
            if (!flagTabOrSpace) {
                flagCurrentIndex = regex_match(tempString.c_str(), operatorR);
                flagTopVector = (!tempVector.empty()) &&
                                !(regex_match(tempVector[tempVector.size() - 1],
                                              operatorR));
                /*
                 * If the current char is operator and the
                 * prev string is not operator.
                 */
                if ((!flagCurrentIndex) && flagTopVector && (!stopToSeparate)) {
                    if (prev == ' ' || prev == '\t') {
                        // separate char indication for the next loop
                        tempVector.push_back("&");
                        tempVector.push_back(tempString);
                        stopToSeparate = true;
                    } else {
                        tempVector.push_back(tempString);
                    }
                // else push the char to the vector
                } else {
                    tempString = tempSubString[i];
                    tempVector.push_back(tempString);
                }
            }
            prev = tempSubString[i];
        }
        tempString = "";
        // merge the strings to two expressions
        for (int j = 0; j < tempVector.size(); ++j) {
            if (tempVector[j] != "&") {
                tempString += tempVector[j];
            } else {
                vec.push_back(tempString);
                tempString = "";
            }
        }
        // push the last string
        if (tempString != "") {
            vec.push_back(tempString);
        }
    }
    // check if the amount of variable is valid
    if (vec.size() == NO_ARGUMENTS && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error no arguments";
    }
    if (vec.size() > TWO_ARGUMENTS && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error to much arguments";
    }
    if (vec.size() == OME_ARGUMENTS && vec[0] != "{" && vec[0] != "}") {
        throw "Syntax Error missing arguments Separate with char ',' ";
    }
    eraseBrackets(&vec, END_LINE, 0);
    return vec;
}

/**
 * Function name: splitLineWithOneArguments
 * The function operation: The function splits function command string with
 * one arguments, check if the amount of variable is valid and erase.
 * brackets by call the function eraseBrackets.
 * @param givenLine
 * @param command the function name
 * @return the split line
 */
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
    // split the brackets
    eraseBrackets(&vec, END_LINE, 0);
    return vec;
}

/**
 * Function name: splitInitializationOperator
 * The function operation: The function splits Initialization Operator command
 * string with one arguments,check if the amount of variable is valid and erase.
 * brackets by call the function eraseBrackets.
 * @param givenLine
 * @return the split line
 */
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
    // split the brackets
    eraseBrackets(&vec, END_LINE, 0);
    return vec;
}

/**
 * Function name: eraseBrackets
 * The function operation: the function erase brackets from given string
 * and add them to the given vector.
 * @param strings
 * @param indication the brackets position
 * @param endOfCheck the end postion
 */
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
        // if there is not a bracket in the start line pop the string.
        strings->pop_back();
    }
}

/**
 * Function name: eraseBrackets
 * The function operation: the function check if substring is a prefix of
 * given string.
 * @param fullString
 * @param prefix
 * @return bool true if yes false if not
 */
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