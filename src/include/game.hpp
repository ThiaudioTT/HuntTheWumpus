#pragma once
#include <vector>
#include <iostream> // debug

#ifndef GAME_HPP
#define GAME_HPP


class Board {
private:
    std::vector<std::vector<int>> cells;

public: 
    /**
     * @brief Construct a new Board object filling the cells
     */
    Board();

};

#endif // GAME_HPP
