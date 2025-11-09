# Socket Tic-Tac-Toe

A multiplayer Tic-Tac-Toe game with client-server architecture using **TCP sockets** and **object-oriented programming** in C++.

## 🎮 Features

- **Network-based gameplay** using TCP protocol
- **Client-server architecture** for two-player games
- **Object-oriented design** with clean class separation
- **Real-time turn-based communication** over sockets
- Cross-platform socket programming (POSIX)

## 🏗️ Architecture & OOP Design

This project demonstrates object-oriented programming principles with the following class structure:

### Classes

- **`Board`**: Manages the 3×3 game grid state, validates moves, checks win conditions, and displays the board
- **`Player`**: Represents individual players with names and symbols ('X' or 'O')
- **`Game`**: Orchestrates game flow, turn management, win/draw detection, and player switching
- **`NetworkManager`**: Handles all TCP socket operations including:
  - Server socket creation, binding, and listening
  - Client socket creation and connection
  - Sending and receiving game moves over the network
  - Connection management and cleanup

### OOP Principles Applied

- **Encapsulation**: Each class manages its own data with private members and public interfaces
- **Abstraction**: Network complexity hidden behind simple `sendBoardMove()` and `recieveMove()` methods
- **Separation of Concerns**: Game logic, board state, and network communication are independent

## 🔌 TCP Socket Implementation

The project uses **POSIX TCP sockets** for reliable, connection-oriented communication:

- **Server Side**: 
  - Creates listening socket with `socket()`
  - Binds to port with `bind()`
  - Listens for connections with `listen()`
  - Accepts client with `accept()` (blocking)
  
- **Client Side**:
  - Creates socket with `socket()`
  - Connects to server with `connect()`

- **Data Transfer**: 
  - `send()` - Transmits move data
  - `recv()` - Receives opponent moves (blocking)

## 🚀 How to Build & Run

### Compile the Project

```bash
make
```

### Run the Game

You need **two terminal windows** - one for the server and one for the client.

#### Terminal 1 - Start Server (Player X)

```bash
./game --server 8080
```

The server will start and wait for a client to connect:
```
Server started on port 8080
Waiting for client to connect...
```

#### Terminal 2 - Connect Client (Player O)

```bash
./game --client 127.0.0.1 8080
```

For playing on the same machine, use `127.0.0.1` (localhost). For different machines, use the server's IP address.

```
Connected to server successfully!
```

### Gameplay

- Server (Player X) goes first
- Enter positions 0-8 to make moves:

```
 0 | 1 | 2
---|---|---
 3 | 4 | 5
---|---|---
 6 | 7 | 8
```

- Players alternate turns automatically
- Game ends when someone wins or the board is full (draw)

### Clean Up

```bash
make clean
```

## 📸 Screenshots

<!-- Add gameplay screenshots here -->

## 🛠️ Technologies

- **Language**: C++ (C++17)
- **Networking**: POSIX TCP Sockets
- **Build System**: Makefile
- **Platform**: macOS/Linux (POSIX-compliant systems)

## 📚 Learning Outcomes

This project demonstrates:
- TCP socket programming with `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `send()`, `recv()`
- Client-server network architecture
- Object-oriented design patterns in C++
- Resource management and cleanup
- Blocking I/O for turn-based games
- Network protocol design for game state synchronization