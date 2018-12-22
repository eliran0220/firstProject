#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <sstream>
#include <cstring>
#include <thread>
#include "ControlSimulator/RunTheSimulator.h"
#include "ServerAndClient/DataReaderClient.h"

static void run(int port);
static int createSocket(int port);

int main() {
    // ליצור את כל המחלקות של הקומאנדים
    // ליצור מחלקה שמחזירה את כל המשתנים var
    // במחלקה יהיה מפה בין מחרוזת לקומאנד
    /*
    try {
        FactoryExpression *f = new FactoryExpression(NULL);
        Expression *e = f->create("5+-(7+8)");
        cout<<e->calculate()<<endl;
    } catch (const char* c) {
        cout<<c<<endl;
    }
     */
    /*
    try {
    FactoryExpression* factoryExpression= new FactoryExpression(NULL);
    Expression* e = factoryExpression->create("3+4/10*20");
    cout<< e->calculate();
    } catch (const char* c) {
        cout<<c<<endl;
    }
    */
    
    //run(5403);
    DataReaderClient::run(5402,"128.0.0.1",NULL,NULL);
    /*
    try {
        RunTheSimulator* r = new RunTheSimulator();
        vector<string> s = r->lexer("test.txt");
        r->parser(s);
    } catch (const char* c) {
        cout<<c<<endl;
    }
     */

    //while (true) {

    //}
    //FactoryExpression* factoryExpression = new FactoryExpression(NULL);
    //Expression* e = factoryExpression->create("(5/2) +5");
    //r->parser(s);
    //delete (r);
    //RunTheSimulator* r = new RunTheSimulator();
    //SymbolTable *symbolTable = new SymbolTable();
    //vector<string> s = r->lexer("test.txt");
    //r->parser(s);


    return 0;
}



static void run(int port) {
    int socket = createSocket(port);
    ssize_t n;
    float buffer[BUFFER];
    bzero(buffer, BUFFER);
    while (true) {
        n = read(socket, buffer, BUFFER - 1);
        cout<<buffer;
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
    }
}

static int createSocket(int port) {
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

    /* Now start listening for the clients, here process willaf
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd, 1);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    cout << "waiting for connection..\n" << endl;
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
                       (socklen_t *) &clilen);
    while (newsockfd < 0) {
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr,
                           (socklen_t *) &clilen);
    }
    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    cout << "connection established";
    return newsockfd;
}







