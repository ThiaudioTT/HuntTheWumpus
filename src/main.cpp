#include <stdlib.h>
#include <iostream>
#include <vector>
#include "./include/game.hpp"

int main()
{
    std::cout << "Hello World!\n";
    Board board;
    board.printBoard();

    Player player(board, 2, 1);

    int move = 1;
    while(true)
    {
        std::cout << "For where? ";
        int decision;
        std::cin >> decision;

        // only testing movement
        player.move(board, 2, move++);

        board.printBoard();

    }
    return 0;
}