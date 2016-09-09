//
// Created by matias on 9/5/16.
//

#ifndef HANDRECOGNITION_CLIENT_H
#define HANDRECOGNITION_CLIENT_H

#include <string>
#include <netinet/in.h>
#include <netdb.h>

class Client {
private:
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    bool connected, ok = true;
public:
    Client(const char * ip, int port);
    ~Client();
    void send(std::string data);

};


#endif //HANDRECOGNITION_CLIENT_H
