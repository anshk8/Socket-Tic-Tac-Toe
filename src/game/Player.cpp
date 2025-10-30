#include "Player.h"

using namespace std;

// Constructor - initialize player with name and symbol
Player::Player(string playerName, char playerSymbol) 
    : name(playerName), symbol(playerSymbol) {
}

// Get player's name
string Player::getName() const {
    return name;
}

// Get player's symbol ('X' or 'O')
char Player::getSymbol() const {
    return symbol;
}
