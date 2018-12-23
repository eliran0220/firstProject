//
// Created by eliran on 12/21/18.
//

#ifndef FIRSTPROJECT_DATAREADERCLIENT_H
#define FIRSTPROJECT_DATAREADERCLIENT_H

#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include "DataReaderServer.h"


#include <string.h>
#include "../Useful/SymbolTable.h"

#define SIZE 1023

using namespace std;

class DataReaderClient {

public:
    static void run(int givePort, string givenIp, SymbolTable *symbolTable,
                    bool *shouldStop);
    static void run2(int givePort, string givenIp, SymbolTable *symbolTable,
                     bool *shouldStop);
    static int createSocket(int port);

    static void writeToServer(int socket, SymbolTable* symbolTable);
};


#endif //FIRSTPROJECT_DATAREADERCLIENT_H
