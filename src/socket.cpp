#include "socket.h"

#include <iostream>
#include <unistd.h>

Socket::Socket(int port) {
    socketID = socket(AF_INET, SOCK_STREAM, 0);
    if (socketID == -1) {
        std::cerr << "Error creating socket\n";
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketID, (struct sockaddr*)&server_address, sizeof(server_address)) == -1) {
        std::cerr << "Error binding socket\n";
        exit(1);
    }

    if (listen(socketID, 10) == -1) {
        std::cerr << "Error listening on socket\n";
        exit(1);
    }
}

int Socket::acceptConnection() {
    return accept(socketID, NULL, NULL);
}

int Socket::recieveData(int client, char* request) {
    char buffer[1024];
    int bytes = recv(client, buffer, sizeof(buffer), 0);
    std::cout << buffer << std::endl;
    return bytes;
}

void Socket::sendData(int client, const char* response) {
    send(client, response, strlen(response), 0);
}

Socket::~Socket() {
    std::cout << "Closing socket: " << socketID << std::endl;
    close(socketID);
}