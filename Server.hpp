#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <winsock2.h>
#include "LibraryManager.hpp"  

class Server {
private:
    int port;
    SOCKET serverSocket;
    LibraryManager libraryManager;

    std::string getLocalIPAddress();
    void handleClient(SOCKET clientSocket);

public:
    Server(int port);
    bool start();
    void acceptAndProcessClientRequests();
    std::string handleRequest(const std::string &clientRequest);
    void stop();
};

#endif
