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

/**
 * @brief Directions for the player and other entities.
 * Note: clockwise order
 */
enum directions {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
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


    /**
     * @brief move the player in a direction one time and 
     * update the previous cell to empty
     * 
     * @param direction use the enum directions
     */
    void move(int direction);
};

#endif // GAME_HPP
