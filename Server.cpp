#include "Server.hpp"
#include <iostream>
#include <sstream>
#include <thread>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib") // for windows sockets API

#define BUFFER_SIZE 1024

Server::Server(int port) : port(port), serverSocket(INVALID_SOCKET) {}

// Method to get Local IP Address of machine
std::string Server::getLocalIPAddress()
{
    char serverName[256];
    if (gethostname(serverName, sizeof(serverName)) == SOCKET_ERROR)
    {
        std::cerr << "Failure in getting server name. Error: " << WSAGetLastError() << "\n";
        return "Unknown";
    }

    struct addrinfo addrInfoHints{}, *addressList, *currentAddress;
    addrInfoHints.ai_family = AF_INET;       // IPv4 address only
    addrInfoHints.ai_socktype = SOCK_STREAM; // TCP

    if (getaddrinfo(serverName, nullptr, &addrInfoHints, &addressList) != 0)
    {
        std::cerr << "Failure in getting local IP address. Error: " << WSAGetLastError() << "\n";
        return "Unknown";
    }

    for (currentAddress = addressList; currentAddress != nullptr; currentAddress = currentAddress->ai_next)
    {
        sockaddr_in *addr = reinterpret_cast<sockaddr_in *>(currentAddress->ai_addr);
        std::string ip = inet_ntoa(addr->sin_addr); // Convert binary IP address into readable string
        freeaddrinfo(addressList);                  // Ensure memory get free
        return ip;
    }

    freeaddrinfo(addressList); // Ensure memory get free in all cases
    return "Unknown";
}

// Method to handle client connection
void Server::handleClient(SOCKET clientSocket)
{
    sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    char buffer[BUFFER_SIZE] = {0};

    while (true)
    {
        int bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (sockaddr *)&clientAddress, &clientAddressSize);
        if (bytesRead <= 0)
        {
            std::cout << "Client disconnected or error occurred.\n";
            break;
        }

        std::string request(buffer, bytesRead);
        std::cout << "Received request: " << request << "\n";

        std::string response = handleRequest(request);
        sendto(clientSocket, response.c_str(), response.size(), 0, (sockaddr *)&clientAddress, clientAddressSize);

        memset(buffer, 0, sizeof(buffer));
    }
}

// Method to check server is started on not
bool Server::start()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Failure in Winsock initialization. Error: " << WSAGetLastError() << "\n";
        return false;
    }

    serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket == INVALID_SOCKET)
    {
        std::cerr << "Failure in socket creation. Error: " << WSAGetLastError() << "\n";
        WSACleanup();
        return false;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cerr << "Failure in socket binding. Error: " << WSAGetLastError() << "\n";
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }

    std::string localIP = getLocalIPAddress();
    std::cout << "Server running on IP: " << localIP << " and port " << port << "...\n";
    return true;
}

// Method to accept and process clients requests
void Server::acceptAndProcessClientRequests()
{
    sockaddr_in clientAddress;
    int clientAddressSize = sizeof(clientAddress);
    char buffer[BUFFER_SIZE] = {0};

    while (true)
    {
        int bytesRead = recvfrom(serverSocket, buffer, sizeof(buffer), 0, (sockaddr *)&clientAddress, &clientAddressSize);
        if (bytesRead <= 0)
        {
            std::cerr << "Error receiving data or client disconnected.\n";
            continue;
        }

        std::string request(buffer, bytesRead);
        std::cout << "Received request: " << request << "\n";

        std::string response = handleRequest(request);
        sendto(serverSocket, response.c_str(), response.size(), 0, (sockaddr *)&clientAddress, clientAddressSize);

        memset(buffer, 0, sizeof(buffer));
    }
}

// Method to handle client action in System
std::string Server::handleRequest(const std::string &request)
{
    if (request.rfind("addBook,", 0) == 0)
    {
        size_t firstComma = request.find(',');
        size_t secondComma = request.find(',', firstComma + 1);
        size_t thirdComma = request.find(',', secondComma + 1);

        std::string bookTitle = request.substr(firstComma + 1, secondComma - firstComma - 1);
        std::string bookAuthor = request.substr(secondComma + 1, thirdComma - secondComma - 1);
        std::string bookISBN = request.substr(thirdComma + 1);

        libraryManager.handleAddBook(bookTitle, bookAuthor, bookISBN);
        return "Book added.";
    }
    else if (request.rfind("removeBook,", 0) == 0)
    {
        std::string bookISBN = request.substr(request.find(',') + 1);
        libraryManager.handleRemoveBook(bookISBN);
        return "Book removed.";
    }
    else if (request.rfind("searchBookByISBN,", 0) == 0)
    {
        std::string bookISBN = request.substr(request.find(',') + 1);
        std::ostringstream oss;
        bool found = false;

        for (const auto &book : libraryManager.getBooks())
        {
            if (book.getBookISBN() == bookISBN)
            {
                found = true;
                oss << "Title: " << book.getTitle()
                    << ", Author: " << book.getBookAuthor()
                    << ", ISBN: " << book.getBookISBN()
                    << ", Available: " << (book.isAvailable() ? "Yes" : "No") << "\n";
            }
        }
        if (!found)
        {
            oss << "Book not found.\n";
        }
        return oss.str();
    }
    else if (request.rfind("searchBookByTitle,", 0) == 0)
    {
        std::string bookTitle = request.substr(request.find(',') + 1);
        std::ostringstream oss;
        bool found = false;

        for (const auto &book : libraryManager.getBooks())
        {
            if (book.getTitle() == bookTitle)
            {
                found = true;
                oss << "Title: " << book.getTitle()
                    << ", Author: " << book.getBookAuthor()
                    << ", ISBN: " << book.getBookISBN()
                    << ", Available: " << (book.isAvailable() ? "Yes" : "No") << "\n";
            }
        }
        if (!found)
        {
            oss << "Book not found.\n";
        }
        return oss.str();
    }
    else if (request.rfind("addUser,", 0) == 0)
    {
        size_t firstComma = request.find(',');
        size_t secondComma = request.find(',', firstComma + 1);

        std::string userID = request.substr(firstComma + 1, secondComma - firstComma - 1);
        std::string userName = request.substr(secondComma + 1);

        libraryManager.handleAddUser(userID, userName);
        return "User added.";
    }
    else if (request.rfind("removeUser,", 0) == 0)
    {
        std::string userID = request.substr(request.find(',') + 1);
        libraryManager.handleRemoveUser(userID);
        return "User removed.";
    }
    else if (request.rfind("borrowBook,", 0) == 0)
    {
        size_t firstComma = request.find(',');
        size_t secondComma = request.find(',', firstComma + 1);
        size_t thirdComma = request.find(',', secondComma + 1);

        std::string bookISBN = request.substr(firstComma + 1, secondComma - firstComma - 1);
        std::string userID = request.substr(secondComma + 1, thirdComma - secondComma - 1);
        std::string bookDueDate = request.substr(thirdComma + 1);

        libraryManager.handleBorrowBook(bookISBN, userID, bookDueDate);
        return "Book borrowed.";
    }
    else if (request.rfind("returnBook,", 0) == 0)
    {
        size_t firstComma = request.find(',');
        size_t secondComma = request.find(',', firstComma + 1);

        std::string bookISBN = request.substr(firstComma + 1, secondComma - firstComma - 1);
        std::string userID = request.substr(secondComma + 1);

        libraryManager.handleReturnBook(bookISBN, userID);
        return "Book returned.";
    }
    else if (request == "displayBooks")
    {
        std::ostringstream oss;
        for (const auto &book : libraryManager.getBooks())
        {
            oss << "Title: " << book.getTitle()
                << ", Author: " << book.getBookAuthor()
                << ", ISBN: " << book.getBookISBN()
                << ", Available: " << (book.isAvailable() ? "Yes" : "No") << "\n";
        }
        return oss.str();
    }
    else if (request == "displayUsers")
    {
        std::ostringstream oss;
        for (const auto &user : libraryManager.getUsers())
        {
            oss << "User ID: " << user.getUserID()
                << ", Name: " << user.getName() << "\n";
        }
        return oss.str();
    }
    else if (request == "displayTransactions")
    {
        std::ostringstream oss;
        for (const auto &transaction : libraryManager.getAllTransactions())
        {
            transaction.displayTransaction();
            oss << transaction << "\n";
        }
        return oss.str();
    }
    else if (request == "saveData")
    {
        libraryManager.saveData();
        return "Data saved.";
    }
    else if (request == "loadData")
    {
        libraryManager.loadData();
        return "Data loaded.";
    }

    return "Invalid Request.";
}

// Method to stop server
void Server::stop()
{
    if (serverSocket != INVALID_SOCKET)
    {
        closesocket(serverSocket);
        WSACleanup();
    }
}
