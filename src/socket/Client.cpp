//
// Created by matias on 9/5/16.
//

#include "Client.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>

Client::Client(const char * ip, int port) {
    this->portno = port;
    server = gethostbyname(ip);
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero((char *) &this->serv_addr, sizeof(this->serv_addr));
    this->serv_addr.sin_family = AF_INET;

    bcopy(this->server->h_addr,
          (char *)&this->serv_addr.sin_addr.s_addr,
          this->server->h_length);

    this->serv_addr.sin_port = htons(this->portno);

    this->connected = (connect(this->sockfd,(struct sockaddr *) &this->serv_addr,sizeof(this->serv_addr)) >= 0);


}

void Client::send(std::string data) {
    std::cout<< data<< std::endl;
    size_t lon = strlen(data.c_str());
    char buffer[lon];
    bzero(&buffer, lon);
    strncpy(buffer, data.c_str(), lon);
    std::cout << data.c_str() << " " << strlen(data.c_str()) << std::endl;
    if(this->connected && ok);
        write(this->sockfd, buffer, lon);
}

Client::~Client() {
    close(this->sockfd);
}