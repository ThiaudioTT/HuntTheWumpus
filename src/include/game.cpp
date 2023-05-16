#include "game.hpp"


Board::Board() {
    std::cout << "Board created!\n";
    constexpr int sizeCells = 6;
    for(int i = 0; i < sizeCells; i++) {
        std::vector<int> line;
        for(int j = 0; j < sizeCells; j++){
            if(i == 0 || i == sizeCells - 1 || j == 0 || j == sizeCells - 1) 
                line.push_back(0);
            else // Here is the board, indeed.
                line.push_back(1);
        }

        cells.push_back(line);
    }
    
}