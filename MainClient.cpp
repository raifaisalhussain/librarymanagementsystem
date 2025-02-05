#include "Client.hpp"

int main()
{
    const std::string serverIP = "192.168.0.117";//IP Address of server
    const int port = 8080;
    Client client(serverIP, port);

    if (!client.connectToServer())
    {
        std::cerr << "Failure in server connection.\n";
        return 0;
    }

    client.menu();
    client.closeConnection();
    return 0;
}
