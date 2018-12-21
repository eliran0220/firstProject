//
// Created by eliran on 12/21/18.
//

#ifndef FIRSTPROJECT_DATAREADERCLIENT_H
#define FIRSTPROJECT_DATAREADERCLIENT_H

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "../Useful/SymbolTable.h"

using namespace std;

class DataReaderClient {
public:
    static void run(int givePort, string &givenIp, SymbolTable *symbolTable,
                    bool *shouldStop);

    static int createSocket(int port);
};


#endif //FIRSTPROJECT_DATAREADERCLIENT_H
