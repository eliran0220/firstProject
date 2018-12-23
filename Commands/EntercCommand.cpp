//
// Created by afik on 12/23/18.
//

#include <iostream>
#include "EntercCommand.h"

EntercCommand::EntercCommand() {}

int EntercCommand::execute(vector<string> &parameters, int position) {
    cout<< "Please wait until connection established:";
    char temp[2];
    fgets(temp, sizeof(temp),stdin);
    return 1;
}
