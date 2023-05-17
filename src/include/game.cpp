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


void Board::printBoard(){
    for(int i = 0; i < cells.size(); i++) {
        for(int j = 0; j < cells[i].size(); j++) {
            std::cout << cells[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void Board::updateCell(int x, int y, int value) {
    std::cout << "Updating cell (" << x << ", " << y << ") to " << value << "\n";
    cells[x][y] = value;
}

Player::Player(Board &_board, int _x, int _y) : board(_board) {
    // todo: add preconditions
    x = _x;
    y = _y;

    // ADD VERIFICATION IF cell is empty
    // ADD VERIFICATION IF cell is not a pit
    // ADD VERIFICATION IF cell is not a wumpus
    // ADD VERIFICATION IF cell is not a bat

    board.updateCell(x, y, definitions::PLAYER);
    isAlive = true;
}

void Player::move(int direction) {
    switch(direction) {
        case directions::UP:
            board.updateCell(x, y, definitions::PASSAGE);
            x-=1;
            board.updateCell(x, y, definitions::PLAYER);
            break;
        case directions::RIGHT:
            board.updateCell(x, y, definitions::PASSAGE);
            y+=1;
            board.updateCell(x, y, definitions::PLAYER);
            break;
        case directions::DOWN:
            board.updateCell(x, y, definitions::PASSAGE);
            x+=1;
            board.updateCell(x, y, definitions::PLAYER);
            break;
        case directions::LEFT:
            board.updateCell(x, y, definitions::PASSAGE);
            y-=1;
            board.updateCell(x, y, definitions::PLAYER);
            break;
        default:
            throw std::invalid_argument("Invalid direction");
    }
}