#include "Board.h"

Board::Board(int _height, int _width, int _winLength) : 
    winLength(_winLength), 
    height(_height),
    width(_width),
    board(_height, std::vector<Cell>(_width, FREE)),
    cellsUsed(0),
    moveNum(0),
    state(GOING) {}

bool Board::canMove(int x, int y) const {
    return isCell(x, y) && board[x][y] == FREE;
}

bool Board::isCell(int x, int y) const {
    return 0 <= x && x < width &&
           0 <= y && y < height;
}

void Board::move(int x, int y, int sign) {
    Cell c = (Cell)sign;

    cellsUsed += (c != FREE) - (board[x][y] != FREE);
    board[x][y] = c;
    if (checkWin(x, y, c)) {
        if (c == O)
            state = WIN_O;
        else
            state = WIN_X;
    }

    moveNum++;
    if (cellsUsed == width * height && state == GOING)
        state = DRAW;
}

bool Board::checkWin(int x, int y, Cell c) {
    std::pair<int, int> dirs[] = {{0, 1}, {1, 0}, {1, 1}, {1, -1}};
    for (std::pair<int, int> d : dirs) {
        int len;
        len = maxLength(x, y, d, c);
        d.first *= -1;
        d.second *= -1;
        len += maxLength(x, y, d, c);
        len -= board[x][y] == c;
        if (len >= winLength)
            return true;
    }
    return false;
}

int Board::maxLength(int x, int y, std::pair<int, int> dir, Cell c) {
    int dx = dir.first, dy = dir.second;
    int xt = x, yt = y;
    int i = 0;
    for (; isCell(xt, yt) && board[xt][yt] == c; i++) {
        xt += dx;
        yt += dy;
    }
    return i;
}

Board::GameState Board::isWin() {
    return state;
}

int Board::getMoveNum() {
    return moveNum;
}

const std::vector<Board::Cell> &Board::operator[](int x) {
    return board[x];
}
