#include <stdlib.h>
#include <iostream>
#include <vector>
#include "./include/game.hpp"

int main()
{
    std::cout << "Hello World!\n";
    Board board;

    Player player(board, 1, 2);
    Wumpus wumpus(board, 2, 2);

    int move = 1;
    while(true)
    {
        board.printBoard();
        std::cout << "For where? ";
        int decision;
        std::cin >> decision;

        // only testing movement
        player.move(decision);


    }
    return 0;
}