#ifndef CLIENT
#define CLIENT

#include "NetworkUser.h"

// Client class, responsible for handling the moves by client, both on server machine and client machine
class Client : public NetworkUser {
private:
    bool isServer = false;
    

public:
    Client(bool isServer)
    {
        this->isServer = isServer;
    }
    
    // provides a move on Client's turn(black pieces)
    std::string getMove(Board originalBoard)
    {
        // check the connection between sockets
        checkConnection();
        
        // if class is instantiated on server machine, get the move from remote machine
        if (isServer)
        {
            // buffer to store the message from client
            char buffer[1024] = { 0 };
            
            std::cout << "Avaiting for the client move..." << std::endl;
            
            // if conenction fails while we are waiting- terminate the program
            if (!recv(clientSocket, buffer, sizeof(buffer), 0))
            {
                std::cout << "Connection was terminated. Shutting down the application." << std::endl;
                exit(1);
            }
            
            std::cout << "Move provided by the client: " << buffer << std::endl;
            
            return buffer;

        }
        
        // if class is instantiated on client machine, get the move from keyboard
        else
        {
            // get keyboard input as a move
            std::cout << "Provide a move: " << std::endl;
            std::string typedMove;
            std::getline(std::cin, typedMove);
            
            const char* message = typedMove.c_str();
            
            std::cout << "Move provided by the client: " << message << std::endl;
            
            // inform the other side of the connection about the move
            send(clientSocket, message, strlen(message), 0);
            
            return typedMove;
        }
    }
    
    // override user method to show proper name of the client
    std::string getName()
    {
        return clientName;
    }
};

#endif //CLIENT
