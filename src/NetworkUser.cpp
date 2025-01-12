#include <iostream>
#include <sys/socket.h>
#include "Board.h"
#include "NetworkUser.h"


std::string NetworkUser::serverName = "";
std::string NetworkUser::clientName = "";
//std::string NetworkUser::lastProvidedMove = "";

int NetworkUser::serverSocket = 0;
int NetworkUser::clientSocket = 0;

sockaddr_in NetworkUser::serverAddress = {};


NetworkUser::~NetworkUser()
{
    shutdown(serverSocket, SHUT_RDWR);
    shutdown(clientSocket, SHUT_RDWR);
        
    close(serverSocket);
    close(clientSocket);
}

NetworkUser::NetworkUser()
{

}

// check if there are any problems associated with the socket
void NetworkUser::checkConnection()
{
    int error = 0;
    socklen_t len = sizeof (error);
    int retval = getsockopt (clientSocket, SOL_SOCKET, SO_ERROR, &error, &len);
    
    if (retval != 0 || error != 0)
    {
        std::cout << "Connection was terminated. Shutting down the application." << std::endl;
        exit(1);
    }
}
