#include "Server.hpp"

int main()
{
    const int port = 8080;
    Server server(port);

    if (!server.start())
    {
        std::cerr << "Failure in startup.\n";
        return 0;
    }

    server.acceptAndProcessClientRequests();
    server.stop();
    return 0;
}
