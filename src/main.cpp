#include <stdlib.h>
#include <iostream>
#include <vector>
#include <limits>
#include "./include/game.hpp"

int main()
{
    Board board;

    // for tests
    Player player(board, 1, 2);
    Wumpus wumpus(board, 2, 2);

    while(player.isPlayerAlive() && wumpus.isWumpusAlive())
    {
        board.printBoard();
        std::cout << '\n' << "Move or shoot?: ";
        char direction;
        std::cin >> direction;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters in input buffer
        std::cout << std::endl;
        switch (direction)
        {
        case '5':
            player.move(UP);
            break;
        case '3':
            player.move(RIGHT);
            break;
        case '2':
            player.move(DOWN);
            break;
        case '1':
            player.move(LEFT);
            break;
        default:
            std::cout << "Invalid move\n";
            break;
        }

        // todo: Wumpus doesn't always move
        std::cout << "\nWumpus is moving...\n";
        wumpus.move(); // tests

        if(wumpus.wumpusFoundPlayer()) {
            std::cout << "Wumpus found you!\n";
            player.killPlayer();
        }
    }

    std::cout << "PLAYER IS FUNCKING DEAD!!!!\n";
    return 0;
}