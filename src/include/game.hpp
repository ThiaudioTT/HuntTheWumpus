#pragma once
#include <vector>
#include <iostream> // debug
#include <ctime>
// #include <unistd.h>
#include <chrono>
#include <thread>

#ifndef GAME_HPP
#define GAME_HPP

enum definitions {
    EMPTY = 0,
    PIT = 1,
    PASSAGE = 2,
    BAT = 3,
    WUMPUS = 4,
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

// UTILITY FUNCTIONS

/**
 * @brief Generate a random int
 * 
 * @param min 
 * @param max 
 * @return int 
 */
int randInt(int min, int max);

class Board {
private:
    std::vector<std::vector<int>> cells;

public: 
    /**
     * @brief Construct a new Board object filling the cells
     */
    Board();

    /**
     * @brief Generate the dangers in the board
     * 
     */
    void populateBoard();

    int getBoardSize() { return cells.size(); }

    int getLineSize(int i) { return cells[i].size(); }

    void printBoard();

    void updateCell(int x, int y, int value);

    int getCell(int i, int j);

};


class Player {
private:
    int x, y;
    bool isAlive;

    // many vars to check if the player found something, refactor this?
    bool foundWumpus;
    bool foundPit;
    bool foundBat;
    Board &board;
public:

    /**
     * @brief Construct a new Player object based on a position
     * @param _x 
     * @param _y 
     */
    Player(Board &_board, int _x, int _y); // passing as reference could be better

    /**
     * @brief Construct a new Player object in a random position
     * 
     * @param _board 
     */
    Player(Board &_board);


    /**
     * @brief move the player in a direction one time and 
     * update the previous cell to empty
     * 
     * @param direction use the enum directions
     * @returns bool if the movement was successful
     */
    bool move(int direction);

    bool isPlayerAlive() { return isAlive; }

    bool playerFoundWumpus() { return foundWumpus; }

    bool playerFoundPit() { return foundPit; }

    bool playerFoundBat() { return foundBat; }

    void killPlayer() { isAlive = false; }

    /**
     * @brief shoots an arrow in a direction and return if the wumpus was killed 
     * 
     * @param direction 
     * @return boolean
     */
    bool shoot(int direction);


    void teleport();
};

class Wumpus {
private:
    // todo: use struct to store the position
    int i, j;
    bool isAlive;
    bool foundPlayer;
    Board &board;
public:
    // define a option to set the position randomly

    Wumpus(Board &_board, int _i, int _j);

    Wumpus(Board &_board);

    
    bool isWumpusAlive() { return isAlive; }

    // todo
    void move();

    bool wumpusFoundPlayer() { return foundPlayer; }

    void killWumpus() { isAlive = false; }
};


class Bat {
private:
    int i, j;
    Board &board;
public:
    Bat(Board &_board, int _i, int _j);
};

class Pit {
private:
    int i, j;
    Board &board;
public:
    Pit(Board &_board, int _i, int _j);

};
#endif // GAME_HPP
