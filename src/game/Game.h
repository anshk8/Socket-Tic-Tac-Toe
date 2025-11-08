#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"

class Game {
private:
    Board board;
    Player player1;
    Player player2;
    int currentPlayerIndex;  // 0 = player1, 1 = player2
    bool gameOver;
    
public:
    // Constructor
    Game();
    
    // Start the game (main game loop)
    void start();
    
    // Play one turn - returns true if move was successful
    bool playTurn(int position);
    
    // Check if game is over
    bool isOver() const;
    
    // Get current player
    Player& getCurrentPlayer();

    Board& getBoard();
    
    // Switch to the other player
    void switchPlayer();
};

#endif // GAME_H
