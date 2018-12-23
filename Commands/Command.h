#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
using namespace std;

/**
 * A abstract class command
 */
class Command{
public:
    virtual int execute(vector<string> &parameters, int position) = 0;

    virtual ~Command(){}
};
#endif
