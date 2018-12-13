#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> splitCommand(const string &givenLine);

int main() {



    return 0;
}


list<vector<string>> lexer(const string &fileName) {
        ifstream file(fileName);
        string line;
        list<vector<string>> command;
        if (file.fail()) {
            cout << "File doesn't exist";
        } else {
            while (!file.eof()) {
                getline(file,line);
            }
            vector<string> vec = splitCommand(line);
            command.push_back(vec);
        }

}

vector<string> splitCommand(const string &givenLine){
    vector<string> vec;
    stringstream ss(givenLine);
    string item;
    while (getline(ss, item, ' ')){
        vec.push_back(item);
    }
    return vec;
}




