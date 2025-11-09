
#include "Board.h"
#include <iostream>

using namespace std;

// Constructor - initialize empty board with numbers 1-9
Board::Board() {
    reset();
}

// Reset board to show position numbers
void Board::reset() {
    for (int i = 0; i < 9; i++) {
        cells[i] = '0' + i;  // Convert to character '0'-'8'
    }
}

bool Board::isCellTaken(int position) const{

    if (cells[position] == 'X' || cells[position] == 'O'){
        return true;
    }
    return false;
}

bool Board::makeMove(int position, char symbol) {

    if (isCellTaken(position)){
        cout << "Position Taken Choose Again!" << endl;
        return false;
    }

    cells[position] = symbol;
    return true;
}

// Check if board is completely full
bool Board::isFull() const {
    for (int i = 0; i < 9; i++) {
        if (!isCellTaken(i)) {
            return false;  
        }
    }
    return true;  // All cells are taken
}

// Check if the given symbol has 3 in a row (win condition)
bool Board::checkWin(char symbol) const {
    // Check all 3 rows
    if (cells[0] == symbol && cells[1] == symbol && cells[2] == symbol) return true;
    if (cells[3] == symbol && cells[4] == symbol && cells[5] == symbol) return true;
    if (cells[6] == symbol && cells[7] == symbol && cells[8] == symbol) return true;
    
    // Check all 3 columns
    if (cells[0] == symbol && cells[3] == symbol && cells[6] == symbol) return true;
    if (cells[1] == symbol && cells[4] == symbol && cells[7] == symbol) return true;
    if (cells[2] == symbol && cells[5] == symbol && cells[8] == symbol) return true;
    
    // Check 2 diagonals
    if (cells[0] == symbol && cells[4] == symbol && cells[8] == symbol) return true;
    if (cells[2] == symbol && cells[4] == symbol && cells[6] == symbol) return true;
    
    return false;  // No win found
}

// Print the board in a nice 3x3 grid
void Board::printBoard() const {
    cout << "\n";
    cout << " " << cells[0] << " | " << cells[1] << " | " << cells[2] << "\n";
    cout << "---|---|---\n";
    cout << " " << cells[3] << " | " << cells[4] << " | " << cells[5] << "\n";
    cout << "---|---|---\n";
    cout << " " << cells[6] << " | " << cells[7] << " | " << cells[8] << "\n";
    cout << "\n";
}

