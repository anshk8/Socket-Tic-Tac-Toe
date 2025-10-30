#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

/*Board should be printable, we should be able to make_move */
class Board
{

private:
    // Board as one array
    array<char, 9> cells;

public:
    // Constructor
    Board();

    // Reset board to empty state
    void reset();

    // Make a move at position (0-8) with symbol ('X' or 'O')
    // Returns true if move was valid, false otherwise
    bool makeMove(int position, char symbol);

    // Check if position is already taken
    bool isCellTaken(int position) const;

    // Check if board is full
    bool isFull() const;

    // Check if a player has won (3 in a row)
    bool checkWin(char symbol) const;

    // Print board to console
    void printBoard() const;
};

#endif