//
// Created by afik on 12/15/18.
//
#include "DataReaderServer.h"
//
// Created by eliran on 12/20/18.
//


void DataReaderServer::run(int port, int rate, SymbolTable *symbolTable,
                           bool *shouldStop) {
    int socket = createSocket(port);
    ssize_t n;
    char buffer[1];
    string values;
    while (!*shouldStop) {
        n = read(socket, buffer, 1);
        while (strcmp(buffer, "\n") != 0 ) {
            values += buffer;
            n = read(socket, buffer, 1);
            if (n < 0) {
                perror("ERROR reading from socket");
                exit(1);
            }
        }
        updateSymbolTable(values, symbolTable);
        values = "";
        sleep(rate / MILLI_SECONDS);
    }
    close(socket);
}

int DataReaderServer::createSocket(int port) {
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, 1);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
                       (socklen_t *) &clilen);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    return newsockfd;
}

void
DataReaderServer::updateSymbolTable(string &values, SymbolTable *symbolTable) {
    string xmlPathsVec[XML_AMOUNT_VARIABLES] = {INDICATE_SPEED, INDICATE_ALT,
                                                PRESSURE_ALT, PITCH_DEG,
                                                ROLL_DEG, IN_PITCH_DEG,
                                                IN_ROLL_DEG,
                                                ENC_INDICATE_ALT,
                                                ENC_PRESURE_ALT, GPS_ALT,
                                                GPS_GRND_SPD, GPS_VERTICAL_SPD,
                                                HEAD_DEG, CMPS_HEAD_DEG,
                                                SLIP_SKID, TURN_RATE, SPEED_FPM,
                                                AILERON, ELEVATOR, RUDDER,
                                                FLAPS, THROTTLE, RPM};
    vector<StoreVarValue<double> *> vec;
    StoreVarValue<double> *tempValues;
    stringstream ss(values);
    string tempString;
    double value;
    for (int i = 0; i < XML_AMOUNT_VARIABLES; ++i) {
        if (getline(ss, tempString, ',') && symbolTable->existsInBindValueMap(xmlPathsVec[i])) {
            value = stod(tempString);
            vec = symbolTable->getVariablesForUpdate(xmlPathsVec[i]);
            for (int j = 0; j < vec.size(); ++j) {
                tempValues = vec[j];
                tempValues->setInitialize(true);
                tempValues->setValue(value);
            }
        }
    }
}



