#include "Game.h"
#include <iostream>

using namespace std;

// Constructor - initialize players and game state
Game::Game() 
    : player1("Player 1", 'X'), 
      player2("Player 2", 'O'),
      currentPlayerIndex(0),
      gameOver(false) {
    // Board auto-initializes with its own constructor
}

// Check if game is over
bool Game::isOver() const {
    return gameOver;
}

// Get the current player
Player& Game::getCurrentPlayer() {
    if (currentPlayerIndex == 0) {
        return player1;
    } else {
        return player2;
    }
}

// Play one turn (placeholder for now)
bool Game::playTurn(int position) {

    Player currPlayer = getCurrentPlayer();
    if (board.makeMove(position, currPlayer.getSymbol() )){
        return true;
    }

    return false;
}

// Start game loop
void Game::start() {
    cout << "\n=== TIC-TAC-TOE GAME START ===" << endl;
    
    // Main game loop - keep playing until game is over
    while (!gameOver) {
        // 1. Show the board
        board.printBoard();
        
        // 2. Get current player
        Player& currentPlayer = getCurrentPlayer();
        cout << currentPlayer.getName() << "'s turn (" 
             << currentPlayer.getSymbol() << ")" << endl;
        
        // 3. Ask for move (position 1-9, we'll convert to 0-8)
        cout << "Enter position (1-9): ";
        int position;
        cin >> position;
        position--;  // Convert 1-9 to 0-8
        
        // 4. Try to make the move
        if (playTurn(position)) {
            // Move successful!
            
            // 5. Check if current player won
            if (board.checkWin(currentPlayer.getSymbol())) {
                board.printBoard();
                cout << "\n🎉 " << currentPlayer.getName() 
                     << " WINS! 🎉\n" << endl;
                gameOver = true;
            }
            // 6. Check if board is full (draw)
            else if (board.isFull()) {
                board.printBoard();
                cout << "\n🤝 It's a DRAW! 🤝\n" << endl;
                gameOver = true;
            }
            // 7. Switch to other player
            else {
                currentPlayerIndex = (currentPlayerIndex == 0) ? 1 : 0;
            }
        } else {
            // Move failed - invalid position or cell taken
            cout << "Invalid move! Try again.\n" << endl;
        }
    }
    
    cout << "Game Over! Thanks for playing!" << endl;
}
