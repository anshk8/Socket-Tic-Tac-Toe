#ifndef COMMON_H
#define COMMON_H

// Common message types for network communication
enum MessageType {
    MOVE,
    WIN,
    DRAW,
    INVALID_MOVE,
    GAME_OVER
};

// Constants for the game
const int BOARD_SIZE = 3;

#endif // COMMON_H