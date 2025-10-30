##### This File is Mainly to take notes about Networking
##### Very Basic, just meant for me to get more familiar with basics

---

# Networking for Tic-Tac-Toe - Complete Beginner's Guide 🌐

## **What is Networking?**

**Simple Definition**: Two computers talking to each other over the internet (or local network).

For your game:
- **Player 1** runs the game on Computer A
- **Player 2** runs the game on Computer B
- They need to **send moves** back and forth

---

## **Key Networking Concepts**

### **1. Client-Server Model**

```
Server (Host - Player 1)          Client (Joiner - Player 2)
┌─────────────────┐              ┌─────────────────┐
│  Starts game    │              │  Joins game     │
│  Waits for      │◄─────────────┤  Connects to    │
│  connection     │   Connect    │  server's IP    │
└─────────────────┘              └─────────────────┘
        │                                 │
        │◄────── "I moved to pos 5" ─────┤
        │                                 │
        ├────── "I moved to pos 2" ──────►│
        │                                 │
        │◄────── "I won!" ───────────────┤
```

---

### **2. Sockets**

**What is a Socket?**
- Like a **telephone** for computers
- An endpoint for sending/receiving data
- Uses **IP address** (phone number) and **port** (extension)

**Example:**
```
IP Address: 192.168.1.100 (identifies the computer)
Port: 8080 (identifies which program on that computer)
```

---

### **3. TCP vs UDP**

We'll use **TCP** (Transmission Control Protocol):

| Feature | TCP | UDP |
|---------|-----|-----|
| Reliability | ✅ Guaranteed delivery | ❌ May lose packets |
| Order | ✅ Messages arrive in order | ❌ May arrive out of order |
| Connection | ✅ Establishes connection first | ❌ Just sends data |
| Speed | Slower (more overhead) | Faster |
| Use Case | **Perfect for turn-based games** | Good for real-time (FPS games) |

**Why TCP for Tic-Tac-Toe?**
- We **need** every move to arrive
- We **need** moves in correct order
- Speed doesn't matter (turn-based)

---

## **How It Works for Your Game**

### **Step 1: Server Starts (Player 1)**
```cpp
1. Create a socket
2. Bind to IP address + port (e.g., 0.0.0.0:8080)
3. Listen for incoming connections
4. Accept connection from client
5. Now connected! Can send/receive data
```

### **Step 2: Client Connects (Player 2)**
```cpp
1. Create a socket
2. Connect to server's IP + port (e.g., 192.168.1.100:8080)
3. Connection established!
4. Now connected! Can send/receive data
```

### **Step 3: Game Loop**
```
Player 1 (Server)           Player 2 (Client)
─────────────────           ─────────────────
Make move (pos 5)
   ├─ send("MOVE:5")────────►  Receive "MOVE:5"
   │                            Update board
   │                            Make move (pos 2)
   │                            send("MOVE:2")
   ◄────────────────────────┤
Receive "MOVE:2"
Update board
...repeat...
```

---

## **Key Networking Terms**

### **IP Address**
- **IPv4**: `192.168.1.100` (four numbers, 0-255)
- Identifies a computer on the network
- `127.0.0.1` = "localhost" (your own computer)

### **Port**
- Number from 0-65535
- Identifies which program/service
- Ports 0-1023 are "reserved" (HTTP=80, HTTPS=443)
- We'll use `8080` or `9999` (common for custom apps)

### **Socket**
- Programming interface for network communication
- Like `cout`/`cin` but for network instead of terminal

### **Bind**
- Server "claims" a port
- Like answering a phone on a specific line

### **Listen**
- Server waits for incoming connections
- Like waiting for phone to ring

### **Accept**
- Server accepts a client connection
- Like picking up the phone

### **Connect**
- Client initiates connection to server
- Like dialing a phone number

### **Send/Recv (Receive)**
- Sending/receiving data through the socket
- Like talking/listening on the phone

---

## **Protocol Design for Tic-Tac-Toe**

We need to define **what messages** to send:

```cpp
// Simple text-based protocol
"MOVE:5"        // Player moved to position 5
"WIN:X"         // Player X won
"DRAW"          // Game is a draw
"RESET"         // Start new game
"QUIT"          // Player disconnected
```

**Why text?** Easy to debug, human-readable!

---

## **What We'll Implement**

### **NetworkManager Class**

```cpp
class NetworkManager {
private:
    int socketFd;           // Socket file descriptor (the "phone")
    bool isServer;          // Are we hosting or joining?
    
public:
    // Server: start hosting on port
    bool startServer(int port);
    
    // Client: connect to server's IP and port
    bool connectToServer(string ip, int port);
    
    // Send a message (e.g., "MOVE:5")
    bool sendMessage(string message);
    
    // Receive a message (blocking - waits for data)
    string receiveMessage();
    
    // Close connection
    void disconnect();
};
```

---

## **Platform-Specific Code**

**On Mac/Linux**, we use:
```cpp
#include <sys/socket.h>    // socket(), bind(), listen()
#include <netinet/in.h>    // sockaddr_in
#include <arpa/inet.h>     // inet_pton()
#include <unistd.h>        // close()
```

**On Windows**, we use:
```cpp
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
```

We'll focus on **Mac/Linux** first!

---

## **Example Flow**

```cpp
// Server (Player 1)
NetworkManager nm;
nm.startServer(8080);  // Listen on port 8080
cout << "Waiting for player 2..." << endl;
// Accept connection happens here
cout << "Player 2 connected!" << endl;

// Client (Player 2)
NetworkManager nm;
nm.connectToServer("192.168.1.100", 8080);
cout << "Connected to player 1!" << endl;

// During game
nm.sendMessage("MOVE:5");       // I moved to position 5
string msg = nm.receiveMessage(); // Wait for opponent's move
// Parse msg -> "MOVE:2" -> opponent moved to position 2
```

---

## **Next Steps**

We'll build `NetworkManager` in baby steps:

1. ✅ **Step 1**: Create socket, understand file descriptors
2. ✅ **Step 2**: Implement `startServer()` (bind, listen, accept)
3. ✅ **Step 3**: Implement `connectToServer()` (connect)
4. ✅ **Step 4**: Implement `sendMessage()` (send data)
5. ✅ **Step 5**: Implement `receiveMessage()` (receive data)
6. ✅ **Step 6**: Test with simple messages
7. ✅ **Step 7**: Integrate with Game class


