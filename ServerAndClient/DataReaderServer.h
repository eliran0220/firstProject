//
// Created by afik on 12/15/18.
//

#ifndef FIRSTPROJECT_DATAREADERSERVER_H
#define FIRSTPROJECT_DATAREADERSERVER_H


#include "../Useful/Factory.h"

class DataReaderServer {

private:
    int port;
    int rate;
public:
    DataReaderServer(int givenPort, int givenRate);

    int run();

    int createSocket(int port);

    string getData(int socketId, int rate);
};


#endif //FIRSTPROJECT_DATAREADERSERVER_H
