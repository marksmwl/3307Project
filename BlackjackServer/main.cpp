#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <cstring>
#include <unistd.h>         
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Include our player class to encapsulate player data.
// We'll store our players in a vector to manipulate their data throughout the game. 
#include "GameLogic/Player.hpp"

// Start a web server, listening for client connections.
int main()
{
    // Create a TCP Socket. 
    int serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock < 0) {
        perror("Socket error");
        return 1;
    }

    // Allow immediate reuse of the address and port.
    int opt = 1;
    if (setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(serverSock);
        return 1;
    }

    // Set up the server address structure.
    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Listen on any available network interface.
    serverAddr.sin_port = htons(12345);         // Listening port.

    // Bind the socket to the specified IP and port.
    if (bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind");
        close(serverSock);
        return 1;
    }

    // Begin listening for incoming connections.
    if (listen(serverSock, 10) < 0) {  // 10 is the backlog of pending connections.
        perror("listen");
        close(serverSock);
        return 1;
    }

    // Initialize the list of player
    std::vector<Player> players;

    std::cout << "Server listening on port 12345..." << std::endl;
    
    // Main loop: accept incoming connections and handle them.
    while (true) {
        // To Do: Connection logic
        
    }

    // Once the game starts, the logic will go here.
    
    close(serverSock);
    return 0;
}