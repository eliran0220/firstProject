//
// Created by afik on 12/15/18.
//

#include "DataReaderServer.h"
//
// Created by eliran on 12/20/18.
//

#define BUFFER 256
#define MILLI_SECONDS 1000

#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>
#include <iostream>
#include "DataReaderServer.h"
#include "../Expressions/Expression.h"

int DataReaderServer::run() {
    int socket = createSocket(this->port);
    string data = getData(socket,this->rate);
    return 3;
}

DataReaderServer::DataReaderServer(int givenPort, int givenRate) {
    this->port = givenPort;
    this->rate = givenRate;
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

    /* Accept actual connection from the client */
    cout << "waiting for connection..";
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
                       (socklen_t *) &clilen);

    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    cout << "connection established";
    return newsockfd;
}

string DataReaderServer::getData(int socketId, int rate) {
    ssize_t n;
    char buffer[BUFFER];
    bzero(buffer, BUFFER);
    n = read(socketId, buffer, BUFFER - 1);
    if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
    }
    sleep(rate / MILLI_SECONDS);
}



