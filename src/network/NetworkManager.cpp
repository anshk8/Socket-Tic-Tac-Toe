#include "NetworkManager.h"
#include <sys/socket.h>
#include <netinet/in.h>
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

}


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
