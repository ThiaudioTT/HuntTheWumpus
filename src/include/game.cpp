#include "game.hpp"


int randInt(int min, int max) {
    // todo
}

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

int Board::getCell(int i, int j) {
    return cells[i][j];
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

bool Player::move(int direction) {
    const int previousX = x;
    const int previousY = y;

    int nextX = x;
    int nextY = y;
    switch(direction) {
        case directions::UP:
            nextX-=1;
            break;
        case directions::RIGHT:
            nextY+=1;
            break;
        case directions::DOWN:
            nextX+=1;
            break;
        case directions::LEFT:
            nextY-=1;
            break;
        default:
            throw std::invalid_argument("Invalid direction");
    }

    if(board.getCell(nextX, nextY) == definitions::EMPTY)
        return false;
  

    x = nextX;
    y = nextY;

    board.updateCell(x, y, definitions::PLAYER);
    board.updateCell(previousX, previousY, definitions::PASSAGE);
    return true;
}

Wumpus::Wumpus(Board &_board, int _x, int _y) : board(_board) {
    i = _x;
    j = _y;

    board.updateCell(i, j, definitions::WUMPUS);
}


void Wumpus::move() {
    // add verification for case bats or pits
    // todo
}