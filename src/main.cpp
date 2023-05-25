#include <stdlib.h>
#include <iostream>
#include <vector>
#include <limits>
#include "./include/game.hpp"
#include <unordered_map>

std::unordered_map<char, int> directions = {
    // translations of the keyboard
    {'1', LEFT},
    {'2', DOWN},
    {'3', RIGHT},
    {'5', UP},
};

int main()
{
    Board board;

    // for tests
    Player player(board, 1, 2);
    Wumpus wumpus(board, 2, 2);

    while (player.isPlayerAlive() && wumpus.isWumpusAlive())
    {
        board.printBoard();
        std::cout << '\n'
                  << "Move or shoot?: ";

        bool isShootingMode = false;

        char direction;
        std::cin >> direction;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore remaining characters in input buffer
        std::cout << std::endl;

        if (direction == '6')
        {
            isShootingMode = true;
            std::cout << "Entering shooting mode...\n"
                      << "Enter the direction you want to shoot: ";
            std::cin >> direction;
        }

        bool isWumpusDeadByArrow = false;
        // todo: refactor this
        switch (direction)
        {
        case '5':
            if (isShootingMode)
                isWumpusDeadByArrow = player.shoot(UP);
            else
                player.move(UP);
            break;
        case '3':
            if (isShootingMode)
                isWumpusDeadByArrow = player.shoot(RIGHT);
            else
                player.move(RIGHT);
            break;
        case '2':
            if (isShootingMode)
                isWumpusDeadByArrow = player.shoot(DOWN);
            else
                player.move(DOWN);
            break;
        case '1':
            if (isShootingMode)
                isWumpusDeadByArrow = player.shoot(LEFT);
            else
                player.move(LEFT);
            break;
        default:
            std::cout << "Invalid direction\n";
            break;
        }
        
        if(isShootingMode) {
            if (isWumpusDeadByArrow)
            {
                std::cout << "You killed the Wumpus!\n";
                wumpus.killWumpus();
                break;
            }

            std::cout << "\nWumpus is moving...\n";
            wumpus.move(); // tests
        }


        if (wumpus.wumpusFoundPlayer())
        {
            std::cout << "Wumpus found you!\n"
                      << "PLAYER IS FUNCKING DEAD!!!!\n";
            player.killPlayer();
        }
    }

    return 0;
}