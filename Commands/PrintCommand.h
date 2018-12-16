//
// Created by eliran on 12/15/18.
//

#ifndef FIRSTPROJECT_PRINTCOMMAND_H
#define FIRSTPROJECT_PRINTCOMMAND_H

#include"string"
#include "Command.h"

using namespace std;

class PrintCommand : public Command{
private:
public:
    int execute(const vector<string> &parameters, int position);

};


#endif //FIRSTPROJECT_PRINTCOMMAND_H
