#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> splitCommand(const string &givenLine);
list<vector<string>> lexer(const string &fileName);
int main() {
    list<vector<string>> list1;
    list1 = lexer("test.txt");
    return 0;
}


list<vector<string>> lexer(const string &fileName) {
        fstream file(fileName);
        if (!file) {
            cout << "File doesn't exist";
        } else {
            list<vector<string>> command;
            string line;
            while (!file.eof()) {
                getline(file,line);
                vector<string> vec = splitCommand(line);
                command.push_back(vec);
            }
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







