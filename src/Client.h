#ifndef CLIENT_H
#define CLIENT_H

#include "NetworkUser.h"

// Client class, responsible for handling the moves by client, both on server machine and client machine
class Client : public NetworkUser {
private:
    bool isServer = false;
    

public:
    Client(bool isServer);
    
    // provides a move on Client's turn(black pieces)
    std::string getMove(Board originalBoard);
    
    // override user method to show proper name of the client
    std::string getName();
};

#endif //CLIENT_H

