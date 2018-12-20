//
// Created by eliran on 12/14/18.
//

#ifndef FIRSTPROJECT_COMMAND_H
#define FIRSTPROJECT_COMMAND_H

#include <string>
#include <vector>
using namespace std;


class Command{
public:
    virtual int execute(vector<string> &parameters, int position) = 0;
};
#endif //FIRSTPROJECT_COMMAND_H
