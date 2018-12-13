#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;

int main() {

    return 0;
}


list<vector<string>> lexer(const string &fileName) {
        ifstream file(fileName);
        string line;
        vector<string> command;
        if (file.fail()) {
            cout << "File doesn't exist";
        } else {
            while (!file.eof()) {
                getline(file,line);
            }

        }

}

vector<string> splitCommand(const string &givenLine){
    vector<string> vec;
    stringstream ss(givenLine);
    string item;
    string delim = " ";
    while (getline(ss, item, delim)){
        vec.push_back(item);
    }
}




