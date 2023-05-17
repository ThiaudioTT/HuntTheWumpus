#pragma once
#include <vector>
#include <iostream> // debug

#ifndef GAME_HPP
#define GAME_HPP

enum definitions {
    PIT = -1,
    EMPTY = 0,
    PASSAGE = 1,
    BAT = 2,
    WUMPUS = 3,
    PLAYER = 5,
};

class Board {
private:
    std::vector<std::vector<int>> cells;

public: 
    /**
     * @brief Construct a new Board object filling the cells
     */
    Board();

    void printBoard();

    void updateCell(int x, int y, int value);

};


class Player {
private:
    int x, y;
    bool isAlive;
    Board &board;
public:

    /**
     * @brief Construct a new Player object based on a position
     * @param _x 
     * @param _y 
     */
    Player(Board &_board, int _x, int _y); // passing as reference could be better

    void move(int x, int y);
};

#endif // GAME_HPP
