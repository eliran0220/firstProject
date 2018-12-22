//
// Created by eliran on 12/21/18.
//

#include <sstream>
#include "DataReaderClient.h"
#include <pthread.h>
#include <thread>


void run2(int givePort, string givenIp, SymbolTable *symbolTable,
                      bool *shouldStop) {
        int sockfd, portno, n;
        struct sockaddr_in serv_addr;
        struct hostent *server;
        // Create a socket point
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        if (sockfd < 0) {
            perror("ERROR opening socket");
            exit(1);
        }

        server = gethostbyname(givenIp.c_str());

        if (server == NULL) {
            fprintf(stderr, "ERROR, no such host\n");
            exit(0);
        }

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(givePort);

        // Now connect to the server
        int tries = 0;

        while (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        }
        // Update the server for changes
        vector<string> changes;
        vector<string>::iterator it;
        string updateMessage = "set /controls/flight/rudder 1\r\n";
        float f = -1;
        while (!*shouldStop) {
            //writeToServer(sockfd, symbolTable);
            n =write(sockfd, updateMessage.c_str(), updateMessage.size());
            /* Send message to the server */
            string t1 = "set /controls/flight/rudder 1\r\n";
            //n = write(socket, tempString.c_str(), tempString.size());
            n = write(sockfd, t1.c_str(), t1.size());

            t1 = "set /controls/flight/rudder -1\r\n";
            n = write(sockfd, t1.c_str(), t1.size());
            // Check if message sent
            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
        }
}



void
DataReaderClient::run(int givePort, string givenIp, SymbolTable *symbolTable,
                      bool *shouldStop) {
    int socket = createSocket(givePort);
    struct sockaddr_in serv_addr;
    struct hostent *server;
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


    while (connect(socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0);
    while (!*shouldStop) {
        writeToServer(socket, symbolTable);
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 250));
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
                             to_string(vec[j]->getValue()) + "\r\n";
                /* Send message to the server */
                string t1 = "set /controls/flight/rudder 1\r\n";
                //n = write(socket, tempString.c_str(), tempString.size());
                n = write(socket, t1.c_str(), t1.size());
                t1 = "set /controls/flight/rudder -1\r\n";
                n = write(socket, t1.c_str(), t1.size());
                cout<< "aaa"<<endl;
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