//
// Created by eliran on 12/21/18.
//

#include "DataReaderClient.h"

void
DataReaderClient::run(int givePort, string givenIp, SymbolTable *symbolTable,
                      bool *shouldStop) {
    int socket = createSocket(givePort);
    int n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char buffer[1024];
    server = gethostbyname(givenIp.c_str());
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char*)server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(givePort);

    /* Now connect to the server */
    while (connect(socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0);
    while (!*shouldStop) {
        writeToServer(socket, symbolTable);
    }
}

void DataReaderClient::writeToServer(int socket, SymbolTable *symbolTable) {
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
    ssize_t n;
    string tempString;
    char buffer[SIZE];
    vector<StoreVarValue<double> *> vec;
    StoreVarValue<double> *temp;
    for (int i = 0; i < XML_AMOUNT_VARIABLES; ++i) {
        if (symbolTable->existsInBindValueMap(xmlPathsVec[i])) {
            vec = symbolTable->getVariablesForUpdate(xmlPathsVec[i]);
            for (int j = 0; j < vec.size(); ++j) {
                tempString = "set " + xmlPathsVec[i] + " " +
                             to_string(vec[j]->getValue());
                /* Send message to the server */
                char c[32] = "set /controls/flight/rudder -1\n";
                n = write(socket, c, strlen(c) + 1);
                if (n < 0) {
                    perror("ERROR writing to socket");
                    exit(1);
                }
            }
        }
    }
}

int DataReaderClient::createSocket(int port) {
    int sockfd;
    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    return sockfd;
}