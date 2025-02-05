#include "Client.hpp"
#include <iostream>
#include <ws2tcpip.h>
#include <string>
#include <cctype>
#include <algorithm>
#pragma comment(lib, "ws2_32.lib") // for windows sockets API for network programming
#define BUFFER_SIZE 1024           // size of buffer

Client::Client(const std::string &address, int port) : address(address), port(port), clientSocket(INVALID_SOCKET) {}

// Function to check client is connected to server or not
bool Client::connectToServer()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "Failed to initialize Winsock. Error: " << WSAGetLastError() << "\n";
        return false;
    }

    clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket == INVALID_SOCKET)
    {
        std::cerr << "Failure to create socket. Error: " << WSAGetLastError() << "\n";
        WSACleanup();
        return false;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(address.c_str());

    if (connect(clientSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cerr << "Connection failure to the server. Error: " << WSAGetLastError() << "\n";
        closesocket(clientSocket);
        WSACleanup();
        return false;
    }

    std::cout << "Connected to the server at " << address << ":" << port << "\n";
    return true;
}

// Function to send request to server
void Client::sendRequest(const std::string &request)
{
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;                         // address family setting
    serverAddress.sin_port = htons(port);                       // setting port
    serverAddress.sin_addr.s_addr = inet_addr(address.c_str()); // ip address

    sendto(clientSocket, request.c_str(), request.size(), 0, (sockaddr *)&serverAddress, sizeof(serverAddress));

    char buffer[BUFFER_SIZE] = {0};
    int serverAddressSize = sizeof(serverAddress);
    int bytesRead = recvfrom(clientSocket, buffer, sizeof(buffer), 0, (sockaddr *)&serverAddress, &serverAddressSize); // UDP-based communication
    if (bytesRead > 0)
    {
        std::string response(buffer, bytesRead);
        std::cout << "Server Response: " << response << "\n";
    }
}

// Function to close connection with server
void Client::closeConnection()
{
    if (clientSocket != INVALID_SOCKET)
    {
        closesocket(clientSocket);
        WSACleanup();
    }
}

// Main display manu funtion
void Client::menu()
{
    while (true)
    {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Remove Book\n";
        std::cout << "3. Search Book\n";
        std::cout << "4. Add User\n";
        std::cout << "5. Remove User\n";
        std::cout << "6. Borrow Book\n";
        std::cout << "7. Return Book\n";
        std::cout << "8. Display Books\n";
        std::cout << "9. Display Users\n";
        std::cout << "10. Display Transactions\n";
        std::cout << "11. Load Data\n";
        std::cout << "12. Save Data\n";
        std::cout << "13. Exit\n";
        std::cout << "Enter your option: ";

        int option;
        std::cin >> option;
        std::cin.ignore();

        std::string requestedAction;
        switch (option)
        {
        case 1:
        {
            std::string bookTitle, bookAuthor, bookISBN;
            std::cout << "Enter book title: ";
            std::getline(std::cin >> std::ws, bookTitle);
            std::cout << "Enter author: ";
            std::getline(std::cin, bookAuthor);
            std::cout << "Enter ISBN(13 digits): ";
            std::getline(std::cin, bookISBN);
            if (!isValidISBN(bookISBN))
            {
                std::cerr << "Invalid ISBN. Enter ISBN in 13 digits only.\n";
                continue;
            }
            requestedAction = "addBook," + bookTitle + "," + bookAuthor + "," + bookISBN;
            break;
        }
        case 2:
        {
            std::string bookISBN;
            std::cout << "Enter 13 Digit ISBN of the book: ";
            std::getline(std::cin >> std::ws, bookISBN);
            requestedAction = "removeBook," + bookISBN;
            break;
        }
        case 3:
        {
            int bookSearchOption;
            std::cout << "Search by:\n1. Book ISBN\n2. Book Title\nEnter your option: ";
            std::cin >> bookSearchOption;
            std::cin.ignore();
            if (bookSearchOption == 1)
            {
                std::string bookISBN;
                std::cout << "Enter 13 digit ISBN: ";
                std::getline(std::cin >> std::ws, bookISBN);
                requestedAction = "searchBookByISBN," + bookISBN;
            }
            else if (bookSearchOption == 2)
            {
                std::string title;
                std::cout << "Enter title: ";
                std::getline(std::cin >> std::ws, title);
                requestedAction = "searchBookByTitle," + title;
            }
            else
            {
                std::cout << "Invalid option.\n";
                continue;
            }
            break;
        }
        case 4:
        {
            std::string userID, userName;
            std::cout << "Enter User ID: ";
            std::getline(std::cin >> std::ws, userID);
            std::cout << "Enter User Name: ";
            std::getline(std::cin, userName);
            requestedAction = "addUser," + userID + "," + userName;
            break;
        }
        case 5:
        {
            std::string userID;
            std::cout << "Enter User ID to remove: ";
            std::getline(std::cin >> std::ws, userID);
            requestedAction = "removeUser," + userID;
            break;
        }
        case 6:
        {
            std::string bookISBN, userID, bookDueDate;
            std::cout << "Enter 13 digit ISBN of the book: ";
            std::getline(std::cin >> std::ws, bookISBN);
            std::cout << "Enter User ID: ";
            std::getline(std::cin, userID);
            std::cout << "Enter Borrow Deadline (YYYY-MM-DD): ";
            std::getline(std::cin, bookDueDate);
            requestedAction = "borrowBook," + bookISBN + "," + userID + "," + bookDueDate;
            break;
        }
        case 7:
        {
            std::string bookISBN, userID;
            std::cout << "Enter 13 digit ISBN of the book: ";
            std::getline(std::cin >> std::ws, bookISBN);
            std::cout << "Enter User ID: ";
            std::getline(std::cin, userID);
            requestedAction = "returnBook," + bookISBN + "," + userID;
            break;
        }
        case 8:
            requestedAction = "displayBooks";
            break;
        case 9:
            requestedAction = "displayUsers";
            break;
        case 10:
            requestedAction = "displayTransactions";
            break;
        case 11:
            requestedAction = "loadData";
            break;
        case 12:
            requestedAction = "saveData";
            break;
        case 13:
            closeConnection();
            return;
        default:
            std::cout << "Enter valid option shown in List.\n";
            continue;
        }

        sendRequest(requestedAction);
    }
}

//Method to check valid length and type of ISBN
bool Client::isValidISBN(const std::string &bookISBN)
{
    if (bookISBN.length() != 13)
    {
        return false;
    }
    return std::all_of(bookISBN.begin(), bookISBN.end(), ::isdigit);
}
