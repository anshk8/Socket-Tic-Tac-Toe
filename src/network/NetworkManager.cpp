#include "NetworkManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

using namespace std;

NetworkManager::NetworkManager()
    : serverSocket(-1),
      clientSocket(-1),
      connected(false),
      isServer(false)
{
    // Clear server address structure
    /*WHY? its a struct and When you declare a struct in C++, its memory contains random leftover data from whatever was there before. This can cause unpredictable behavior. */
    memset(&serverAddress, 0, sizeof(serverAddress));
}

NetworkManager::~NetworkManager(){
    // Clean up any open sockets
    closeConnection();
}


//Source https://www.geeksforgeeks.org/cpp/socket-programming-in-cpp/
bool NetworkManager::startServer(int port){
    // Create server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        cerr << "Failed to create server socket" << endl;
        return false;
    }

    // Configure server address using member variable
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);  // Use the parameter
    serverAddress.sin_addr.s_addr = INADDR_ANY;  // Accept connections on any interface

    // Bind socket to address, returns 0 if good else -1 if unsuccessfull. 
    if (::bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "Failed to bind socket to port " << port << endl;
        close(serverSocket);
        return false;
    }

    // Start listening for connections (backlog of 5)
    if (listen(serverSocket, 5) < 0) {
        cerr << "Failed to listen on socket" << endl;
        close(serverSocket);
        return false;
    }

    // Mark that we're the server
    isServer = true;
    cout << "Server started on port " << port << endl;
    return true;
}

bool NetworkManager::acepetConnection(){
    // Make sure we're running as a server
    if (!isServer || serverSocket == -1) {
        cerr << "Not running as server or server not started" << endl;
        return false;
    }

    cout << "Waiting for client to connect..." << endl;

    // Accept incoming connection (blocks until client connects)
    /*Purpose: To store information about the connecting client (their IP address and port).*/
    sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    
    // accept() returns a NEW socket for communication with this client
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);
    
    if (clientSocket < 0) {
        cerr << "Failed to accept connection" << endl;
        return false;
    }

    // Mark as connected
    connected = true;
    cout << "Client connected successfully!" << endl;
    return true;
}

bool NetworkManager::connectToServer(string ip, int port){
    // Create client socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        cerr << "Failed to create client socket" << endl;
        return false;
    }

    // Configure server address to connect to
    // specifying address
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;



    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        cerr << "Failed to connect to server" << endl;
        close(clientSocket);
        return false;
    }

    // Mark as connected (but not as server)
    connected = true;
    isServer = false;
    cout << "Connected to server successfully!" << endl;
    return true;
}


  // Communication functions 
bool NetworkManager:: sendBoardMove(int pos){
        //TODO
}
    
    // TODO: Create a function to receive a move
    // Parameters: reference to int (to store received position)
    // Returns: bool (success/failure)
bool NetworkManager::recieveMove(int &receivedPos){
        //TODO
}

// Utility function to check connection status
bool NetworkManager::isConnected(){
    return connected;
}

// Utility function to close connection gracefully
void NetworkManager::closeConnection(){
    // Close client socket if open
    if (clientSocket != -1) {
        close(clientSocket);
        clientSocket = -1;
        cout << "Client socket closed" << endl;
    }

    // Close server socket if open (only if we're the server)
    if (serverSocket != -1 && isServer) {
        close(serverSocket);
        serverSocket = -1;
        cout << "Server socket closed" << endl;
    }

    // Reset connection state
    connected = false;
    isServer = false;
}