#ifndef SERVER
#define SERVER

#include "NetworkUser.h"
#include <arpa/inet.h>

// Server class handles the connections between client and server
// also responsible for handling the moves by the server, both on server machine and client machine
class Server : public NetworkUser {
private:
    bool isServer = false;
    
public:
    Server(bool isServer)
    {
        this->isServer = isServer;
        
        // if class is instantiated on server machine, setup a server on current machine
        if (isServer)
        {
            std::cout << "Provide the name of server player: " << std::endl;
            std::getline(std::cin, serverName);
            startupServerOnThisMachine();
        }
        
        // connect client to the server
        else
        {
            std::cout << "Provide the name of client player: " << std::endl;
            std::getline(std::cin, clientName);
            connectThisMachineToserver();
        }
    }
    
    // provides a move on Server's turn(red pieces)
    std::string getMove(Board originalBoard)
    {
        // check the connection between sockets
        checkConnection();
                        
        // if class is instantiated on server machine, get the move from keyboard
        if (isServer)
        {
            std::cout << "Provide a move: " << std::endl;
            std::string typedMove;
            std::getline(std::cin, typedMove);
                        
            // convert move to c style string
            const char* message = typedMove.c_str();
            
            std::cout << "Move provided by the server: " << message << std::endl;
            
            // inform the other side of the connection about the move
            send(clientSocket, message, strlen(message), 0);
            
            return typedMove;
        }
        
        // if class is instantiated on client machine, get the move from remote machine
        else
        {
            // buffer to store the message from server
            char buffer[1024] = { 0 };
            
            std::cout << "Avaiting for the server move..." << std::endl;
            
            // if conenction fails while we are waiting- terminate the program
            if (!recv(clientSocket, buffer, sizeof(buffer), 0))
            {
                std::cout << "Connection was terminated. Shutting down the application." << std::endl;
                exit(1);
            }
            
            std::cout << "Move provided by the server: " << buffer << std::endl;
            
            return buffer;
        }
    }
    
    // establish connection from client to server
    void connectThisMachineToserver()
    {
        std::cout << "\nProvide the ip of a server to connect to (127.0.0.1 for same machine):" << std::endl;
        
        const char* serverIP;

        // get the IP from user
        std::string ipInput;
        std::getline(std::cin, ipInput);
        
        serverIP = ipInput.c_str();
        
        // input validation
        while (inet_addr(serverIP) == -1)
        {
            std::cout << "Adress is invalid, try again" << std::endl;
            std::getline(std::cin, ipInput);
            serverIP = ipInput.c_str();
        }
        
        // create socket file descriptor
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        
        // get all the server attributes and store it in server file descriptor
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(9000);
        serverAddress.sin_addr.s_addr = inet_addr(serverIP); // listens to all NIC 
        
        // connect client to machine
        connect(clientSocket, (struct sockaddr*)&serverAddress,sizeof(serverAddress));
        
        const char* message = clientName.c_str();
        
        // send the client name to server
        send(clientSocket, message, strlen(message), 0);
        
        char buffer[1024] = { 0 };
        
        // receive the server name from the server
        recv(clientSocket, buffer, sizeof(buffer), 0);
        serverName = buffer;
        
        std::cout << "Successfully established conenction with a server(" << serverName << "). Game started."  << std::endl;
    }
    
    // establish connection from server to client
    void startupServerOnThisMachine()
    {
        // create server file descriptor
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        
        // allows binding even if socket is in TIME_WAIT
        int opt = 1;
        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        std::cout << "\nWaiting for a client to connect..." << std::endl;
        
        // get all the server attributes and store it in server file descriptor
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(9000);
        serverAddress.sin_addr.s_addr = INADDR_ANY; // listens to all NIC 
        
        // bind server socket to all NICs
        bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));
    
        listen(serverSocket, 1);
        
        // creates a client conenction socket on the server
        clientSocket = accept(serverSocket, nullptr, nullptr);
        
        char buffer[1024] = { 0 };
        
        // receive the client name from the client
        recv(clientSocket, buffer, sizeof(buffer), 0);
        
        clientName = buffer;
        
        std::cout << "Successfully established conenction with a client(" << clientName << "). Game started."  << std::endl;
        
        // send the server name to the client
        const char* message = serverName.c_str();
        send(clientSocket, message, strlen(message), 0);
    }
    
    // override user method to show proper name of the client
    std::string getName()
    {
        return serverName;
    }
};

#endif //SERVER
