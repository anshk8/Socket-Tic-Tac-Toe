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

// Get board reference
Board& Game::getBoard() {
    return board;
}

// Switch to the other player
void Game::switchPlayer() {
    currentPlayerIndex = (currentPlayerIndex == 0) ? 1 : 0;
}
