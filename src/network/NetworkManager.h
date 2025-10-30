#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <string>
#include <netinet/in.h>  

using namespace std;

class NetworkManager {
private:
    // Socket file descriptors
    // TODO: Add an int for the server socket (listening socket)
    int serverSocket;

    // TODO: Add an int for the client socket (connection to opponent)
    int clientSocket;

    // Server address structure (used for binding)
    // TODO: Add a sockaddr_in struct to store server address info
    sockaddr_in serverAddress;

    // Connection state
    // TODO: Add a bool to track if we're connected
    // TODO: Add a bool to track if we're the server or client
    
public:
    // Constructor
    NetworkManager();
    
    // Destructor - important for cleaning up sockets!
    // TODO: Implement destructor to close any open sockets
    ~NetworkManager();
    
    // Server functions
    // TODO: Create a function to start server (listen on a port)
    // Parameters: port number
    // Returns: bool (success/failure)
    
    // TODO: Create a function to accept incoming connection
    // Returns: bool (success/failure)
    
    // Client functions
    // TODO: Create a function to connect to server
    // Parameters: IP address (string), port number
    // Returns: bool (success/failure)
    
    // Communication functions
    // TODO: Create a function to send a move (position number)
    // Parameters: int position
    // Returns: bool (success/failure)
    
    // TODO: Create a function to receive a move
    // Parameters: reference to int (to store received position)
    // Returns: bool (success/failure)
    
    // Utility functions
    // TODO: Create a function to check if connected
    // Returns: bool
    
    // TODO: Create a function to close connection gracefully
};

#endif // NETWORKMANAGER_H

/* 
 * LEARNING NOTES:
 * 
 * Key TCP Concepts You'll Need:
 * 
 * 1. SOCKET CREATION: socket() function
 *    - Creates an endpoint for communication
 *    - Returns a file descriptor (just an int)
 * 
 * 2. SERVER SIDE:
 *    - bind() - associates socket with an address/port
 *    - listen() - marks socket as passive (waiting for connections)
 *    - accept() - blocks until client connects, returns new socket for that client
 * 
 * 3. CLIENT SIDE:
 *    - connect() - initiates connection to server
 * 
 * 4. DATA TRANSFER:
 *    - send() or write() - sends data through socket
 *    - recv() or read() - receives data from socket
 * 
 * 5. CLEANUP:
 *    - close() - closes socket file descriptor
 * 
 * Header Files You'll Need in NetworkManager.cpp:
 *    - <sys/socket.h>   // Core socket functions
 *    - <netinet/in.h>   // Internet address structures
 *    - <arpa/inet.h>    // inet_addr(), inet_ntoa()
 *    - <unistd.h>       // close(), read(), write()
 * 
 * Game Flow Example:
 * 1. One player creates server: startServer(8080)
 * 2. Other player connects: connectToServer("192.168.1.5", 8080)
 * 3. Players take turns: sendMove(3), receiveMove(&position)
 */
