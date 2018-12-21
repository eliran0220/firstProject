//
// Created by eliran on 12/21/18.
//

#ifndef FIRSTPROJECT_DATAREADERCLIENT_H
#define FIRSTPROJECT_DATAREADERCLIENT_H

#include <string>
#include "../Useful/SymbolTable.h"

using namespace std;

class DataReaderClient {
private:
    int port;
    string ip;
    SymbolTable *symbolTable;
public:
    DataReaderClient(int givePort, string &givenIp, SymbolTable *symbolTable);

    int run();

    int createSocket(int port);

    void setDataToSimulator();

    ~DataReaderClient();

};


#endif //FIRSTPROJECT_DATAREADERCLIENT_H
