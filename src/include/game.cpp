#include "game.hpp"

int randInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void dangerSense(Player &player, Board &board) {
    std::vector<int> dangers = player.cellsAroundPlayer();
    for(int i = 0; i < dangers.size(); i++)
    {
        const int danger = dangers[i];
        switch (danger)
        {
            case definitions::PIT:
                std::cout << "You feel a breeze.\n";
                break;
            case definitions::BAT:
                std::cout << "You hear a flapping.\n";
                break;
            case definitions::WUMPUS:
                std::cout << "You smell a wumpus.\n";
                break;
            default:
                break;
        }
    }
}

Board::Board() {
    std::cout << "Board created!\n";
    constexpr int sizeCells = 9;
    for(int i = 0; i < sizeCells; i++) {
        std::vector<int> line;
        for(int j = 0; j < sizeCells; j++){
            if(i == 0 || i == sizeCells - 1 || j == 0 || j == sizeCells - 1) 
                line.push_back(definitions::EMPTY);
            else // Here is the board, indeed.
                line.push_back(definitions::PASSAGE);
        }

        cells.push_back(line);
    }
    
}

void Board::populateBoard()
{
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[i].size(); j++)
        {
            const int cell = cells[i][j];
            if (cell == definitions::EMPTY || cell == definitions::WUMPUS || cell == definitions::PLAYER)
                continue;

            const int random = randInt(0, 6); // 1/6 chance of being a pit or a bat
            if (random == definitions::PIT || random == definitions::BAT)
            {
                if (random == definitions::PIT)
                    updateCell(i, j, definitions::PIT);
                else
                    updateCell(i, j, definitions::BAT);
            }
        }
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
    // std::cout << "Updating cell (" << x << ", " << y << ") to " << value << "\n";
    cells[x][y] = value;
}

int Board::getCell(int i, int j) {
    if(i < 0 || i >= cells.size() || j < 0 || j >= cells[i].size()) return -1;

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
    foundWumpus = false;
    foundPit = false;
    foundBat = false;
}

Player::Player(Board &_board) : board(_board) {

    foundWumpus = false;
    foundPit = false;
    foundBat = false;

    int positionI = randInt(1, board.getBoardSize() - 1);
    int positionJ = randInt(1, board.getLineSize(positionI) - 1);
    int nextCell = board.getCell(positionI, positionJ);
    while(
        nextCell == definitions::EMPTY ||
        nextCell == definitions::PIT ||
        nextCell == definitions::WUMPUS ||
        nextCell == definitions::BAT
    ) {
        positionI = randInt(1, board.getBoardSize() - 1);
        positionJ = randInt(1, board.getLineSize(positionI) - 1);
        nextCell = board.getCell(positionI, positionJ);
    }

    x = positionI;
    y = positionJ;
    // std::cout << "Player created at (" << x << ", " << y << ")\n";
    board.updateCell(x, y, definitions::PLAYER);
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

    const int nextCell = board.getCell(nextX, nextY);
    if(nextCell == definitions::EMPTY)
        return false;
    switch(nextCell){
        case definitions::EMPTY:
            return false;
            break;
        case definitions::WUMPUS:
            isAlive = false;
            foundWumpus = true;
            return true;
            break;
        case definitions::PIT:
            isAlive = false;
            foundPit = true;
            return true;
            break;
        case definitions::BAT:
            foundBat = true;
            break;
    }

    x = nextX;
    y = nextY;

    board.updateCell(x, y, definitions::PLAYER);
    board.updateCell(previousX, previousY, definitions::PASSAGE);
    return true;
}

bool Player::shoot(int direction) {
    int nextI = x;
    int nextJ = y;

    constexpr int arrowRange = 3;

    switch(direction) {
        case directions::UP:
        // todo: search for better implementation
            for(int i = 0; i < arrowRange; i++) {
                nextI--;
                if(board.getCell(nextI, y) == definitions::WUMPUS) return true;
            }
            break;
        case directions::RIGHT:
            for(int i = 0; i < arrowRange; i++) {
                nextJ++;
                if(board.getCell(x, nextJ) == definitions::WUMPUS) return true;
            }
            break;
        case directions::DOWN:
            for(int i = 0; i < arrowRange; i++) {
                nextI++;
                if(board.getCell(nextI, y) == definitions::WUMPUS) return true;
            }
            break;
        case directions::LEFT:
            for(int i = 0; i < arrowRange; i++) {
                nextJ--;
                if(board.getCell(x, nextJ) == definitions::WUMPUS) return true;
            }
            break;
        default:
            throw std::invalid_argument("Invalid direction");
    }

    return false;
}

void Player::teleport() {
    int positionI = randInt(1, board.getBoardSize() - 1);
    int positionJ = randInt(1, board.getLineSize(positionI) - 1);
    int nextCell = board.getCell(positionI, positionJ);
    while(nextCell == definitions::EMPTY || nextCell == definitions::PIT || nextCell == definitions::WUMPUS || nextCell == definitions::BAT) {
        positionI = randInt(1, board.getBoardSize() - 1);
        positionJ = randInt(1, board.getLineSize(positionI) - 1);
        nextCell = board.getCell(positionI, positionJ);
    }

    board.updateCell(x, y, definitions::PASSAGE);
    x = positionI;
    y = positionJ;
    board.updateCell(x, y, definitions::PLAYER);
    foundBat = false;
}


std::vector<int> Player::cellsAroundPlayer() {
    std::vector<int> cellsAround;
    return { // is this the best way to do this? Because I think this is the laziest one
        board.getCell(x-1, y),
        board.getCell(x, y+1),
        board.getCell(x+1, y),
        board.getCell(x, y-1)
    };
}

Wumpus::Wumpus(Board &_board, int _x, int _y) : board(_board) {
    i = _x;
    j = _y;

    foundPlayer = false;
    isAlive = true;

    board.updateCell(i, j, definitions::WUMPUS);
}

Wumpus::Wumpus(Board &_board): board(_board) {
    isAlive = true;
    foundPlayer = false;

    int positionI = randInt(1, board.getBoardSize() - 1);
    int positionJ = randInt(1, board.getLineSize(positionI) - 1);
    int nextCell = board.getCell(positionI, positionJ);
    while(
        nextCell == definitions::EMPTY ||
        nextCell == definitions::PIT ||
        nextCell == definitions::PLAYER ||
        nextCell == definitions::BAT
    ) {
        positionI = randInt(1, board.getBoardSize() - 1);
        positionJ = randInt(1, board.getLineSize(positionI) - 1);
        nextCell = board.getCell(positionI, positionJ);
    }

    i = positionI;
    j = positionJ;
    // std::cout << "Wumpus created at (" << i << ", " << j << ")\n";
    board.updateCell(i, j, definitions::WUMPUS);
}


void Wumpus::move() {
    if(!isAlive) throw std::invalid_argument("Wumpus is dead");
    // add verification for case bats or pits

    // todo: search for the case when the wumpus is generated at the corner and have pits around them
    // or refactor that
    
    int direction = randInt(0, 3);
    int nextI = i;
    int nextJ = j;

    int nextCell = definitions::EMPTY;
    while( 
        nextCell == definitions::PIT ||
        nextCell == definitions::EMPTY
    )
    {
        nextI = i;
        nextJ = j;
        direction = randInt(0, 3);
        switch(direction) {
            case directions::UP:
                nextI-=1;
                break;
            case directions::RIGHT:
                nextJ+=1;
                break;
            case directions::DOWN:
                nextI+=1;
                break;
            case directions::LEFT:
                nextJ-=1;
                break;
            default:
                throw std::invalid_argument("Invalid direction");
        }

        nextCell = board.getCell(nextI, nextJ);
    }

    board.updateCell(i, j, definitions::PASSAGE);
    foundPlayer = nextCell == definitions::PLAYER;
    i = nextI;
    j = nextJ;
    board.updateCell(i, j, definitions::WUMPUS);
}


Bat::Bat(Board &_board, int _x, int _y) : board(_board) {
    i = _x;
    j = _y;

    board.updateCell(i, j, definitions::BAT);
}

Pit::Pit(Board &_board, int _x, int _y) : board(_board) {
    i = _x;
    j = _y;

    board.updateCell(i, j, definitions::PIT); // todo: adds verification if cell is not empty or empty
}
