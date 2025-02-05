#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>
#include <winsock2.h>
#include <iostream>


class Client {
private:
    std::string address;
    int port;
    SOCKET clientSocket;

public:
    Client(const std::string &address, int port);
    bool connectToServer();
    void sendRequest(const std::string &request);
    void closeConnection();
    void menu();
    bool isValidISBN(const std::string &bookISBN);
};

#endif
