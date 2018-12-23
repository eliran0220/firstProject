//
// Created by eliran on 12/21/18.
//

#include <sstream>
#include "DataReaderClient.h"
#include <pthread.h>
#include <thread>


void
DataReaderClient::run(int givePort, string givenIp, SymbolTable *symbolTable,
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
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr,
          server->h_length);
    serv_addr.sin_port = htons(givePort);

    // Now connect to the server
    int tries = 0;

    while (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) <
           0) {
    }
    // Update the server for changes
    vector<string> changes;
    vector<string>::iterator it;
    string updateMessage = "set /controls/flight/rudder 1\r\n";
    float f = -1;
    while (!*shouldStop) {
        writeToServer(sockfd, symbolTable);
        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
        this_thread::sleep_for(std::chrono::milliseconds((unsigned int) 250));
    }
    close(sockfd);
}


void DataReaderClient::writeToServer(int socket, SymbolTable *symbolTable) {
    ssize_t n;
    string tempString;
    char buffer[SIZE];
    map<string, vector<StoreVarValue<double> *>> bindsValues =
                                                 symbolTable->getBindMap();

    map<string, vector<StoreVarValue<double> *>>::iterator it =
                                                  bindsValues.begin();
    while (it != bindsValues.end()) {
        for (int i = 0; i < it->second.size(); ++i) {
            tempString = "set " + it->first + " " +
                         to_string(it->second[i]->getValue()) + "\r\n";
            n = write(socket, tempString.c_str(), tempString.size());
            if (n < 0) {
                perror("ERROR writing to socket");
                exit(1);
            }
        }
        it++;
    }
}