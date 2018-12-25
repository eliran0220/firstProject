#ifndef DATAREADERCLIENT_H
#define DATAREADERCLIENT_H

#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <pthread.h>
#include <thread>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include "../Useful/SymbolTable.h"

#define SIZE 1023

using namespace std;

/**
 * The class DataReaderClient create a client by given ip and port.
 */
class DataReaderClient {

public:
    static void run(int givePort, string givenIp, SymbolTable *symbolTable,
                    bool *shouldStop);
    static void writeToServer(int socket, SymbolTable* symbolTable);
};


#endif