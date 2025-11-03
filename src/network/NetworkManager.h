#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <string>
#include <netinet/in.h>  

using namespace std;

class NetworkManager {
private:
    // Socket file descriptors
    // Server socket (listening socket)
    int serverSocket;

    //Client socket (connection to opponent)
    int clientSocket;

    // Store server address info
    sockaddr_in serverAddress;

    // Track if we're connected
    bool connected;

    //Track if we're the server or client
    bool isServer;
    
public:
    // Constructor
    NetworkManager();
    
    // Destructor - important for cleaning up sockets!
    // TODO: Implement destructor to close any open sockets
    ~NetworkManager();
    
    // Server functions
    //Function to start server (listen on a port)
    bool startServer(int port);
    
    // Function to accept incoming connection
    bool acepetConnection();
    
    // Client functions
    //Function to connect to server
    bool connectToServer(string ip, int port);

    // Communication functions
    // Function to send a move (position number)
    bool sendBoardMove(int pos);
    
    //Function to receive a move
    bool recieveMove(int &receivedPos);
    
    // Utility functions
    //Check if connected
    bool isConnected();

    // Close connection gracefully do cleanup
    void closeConnection();
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
