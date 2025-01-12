#ifndef SERVER_H
#define SERVER_H

#include "NetworkUser.h"
#include <arpa/inet.h>

// Server class handles the connections between client and server
// also responsible for handling the moves by the server, both on server machine and client machine
class Server : public NetworkUser {
private:
    bool isServer = false;
    
public:
    Server(bool isServer);
    
    // provides a move on Server's turn(red pieces)
    std::string getMove(Board originalBoard);
    
    // establish connection from server to client
    void startupServerOnThisMachine();
    
    // establish connection from client to server
    void connectThisMachineToserver();
    
    // override user method to show proper name of the client
    std::string getName();
};

#endif //SERVER_H

