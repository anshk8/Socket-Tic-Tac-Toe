
#include "network/NetworkManager.h"
#include "game/Game.h"
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    NetworkManager netManager;

    // Parse command line arguments
    if (argc < 2)
    {
        cout << "Usage: " << endl;
        cout << "  Server: ./game --server <port>" << endl;
        cout << "  Client: ./game --client <ip> <port>" << endl;
        return 1;
    }

    string mode = argv[1];
    bool myTurn = false; // Declare outside if blocks

    // Setup connection
    if (mode == "--server")
    {
        int port = stoi(argv[2]);
        netManager.startServer(port);
        netManager.accepetConnection();
        // Server goes first
        myTurn = true;
    }
    else if (mode == "--client")
    {
        string ip = argv[2];
        int port = stoi(argv[3]);
        netManager.connectToServer(ip, port);
        // Client goes second
        myTurn = false;
    }

    Game game;
    // GAME LOOP
    while (!game.isOver())
    {
        game.getBoard().printBoard();

        while (myTurn)
        {
            // Get input and send
            cout << game.getCurrentPlayer().getName() << "'s turn ("
                 << game.getCurrentPlayer().getSymbol() << ")" << endl;
            cout << "Enter position (0-8): ";
            int pos;
            cin >> pos;

            // Try to make the move
            if (game.playTurn(pos))
            {
                netManager.sendBoardMove(pos);
                game.switchPlayer();  // Switch to opponent
                myTurn = false;
            }
            else
            {
                cout << "Invalid move! Try again." << endl;
            }
        }
        while (!myTurn)
        {
            // Opponent's turn: receive and update
            cout << "Waiting for opponent..." << endl;
            int opponentPos;
            netManager.recieveMove(opponentPos);
            game.playTurn(opponentPos);
            game.switchPlayer();  // Switch back to me
            myTurn = true;
        }

        // Check who won
        if (game.getBoard().checkWin('X'))
        {
            cout << "\n🎉 Player X WINS! 🎉\n"
                 << endl;
            break;
        }
        else if (game.getBoard().checkWin('O'))
        {
            cout << "\n🎉 Player O WINS! 🎉\n"
                 << endl;
            break;
        }
    }

    // Game over - display final board
    game.getBoard().printBoard();

    // Check who won
    if (game.getBoard().checkWin('X'))
    {
        cout << "\n🎉 Player X WINS! 🎉\n"
             << endl;
    }
    else if (game.getBoard().checkWin('O'))
    {
        cout << "\n🎉 Player O WINS! 🎉\n"
             << endl;
    }
    else
    {
        cout << "\n🤝 It's a DRAW! 🤝\n"
             << endl;
    }

    netManager.closeConnection();

    return 0;
}