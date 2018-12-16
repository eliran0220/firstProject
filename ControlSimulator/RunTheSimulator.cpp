//
// Created by afik on 12/13/18.
//




#include "RunTheSimulator.h"

RunTheSimulator::RunTheSimulator() {
    this->collectionCommands = new CollectionCommands();
}

RunTheSimulator::~RunTheSimulator() {
    delete (this->collectionCommands);
}


void RunTheSimulator::parser(vector<string> commands){
    Expression* command;
    int i = 0;
    while (i < commands.size()){
        command = this->collectionCommands->getExpressionCommand(commands[i]);
        command->setLexerStringAndPosition(commands, i);
        i += (int)command->calculate();
    }
}
/*
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
        temp = splitCommand(line);
        commands.insert(commands.end(), temp.begin(), temp.end());
    }
    file.close();
    return commands;
}
/*
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
 */


vector<string> RunTheSimulator::splitCommand(const string &givenLine) {
    vector<string> vec;
    stringstream ss(givenLine);
    string item;
    getline(ss, item, ' ');
    while (getline(ss, item, ' ')) {
        if (strcmp(item.c_str(), "") == EQUAL ) {
            continue;
        } else if (strcmp(item.c_str(), "=") == EQUAL) {
            vec.push_back(item);
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
        }
        /*
        else if (strstr(item.c_str(), "{") && !strstr(item.c_str(), " ")) {
            vec.push_back(item);
            stringstream temp(item);
            getline(temp, item, '{');
            vec.push_back(item);
            getline(ss, item);
            vec.push_back(item);
        }
         */
        else if (!strstr(item.c_str(), " ")) {
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

/*
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
 */

/*
bool checkIfLineIsConditionCommand(const string &givenLine) {

    return strstr(givenLine.c_str(), WHILE_LOOP) ||
           strstr(givenLine.c_str(), FOR_LOOP)
           || strstr(givenLine.c_str(), IF);

}
*/


