#pragma once

#include <vector>


class Board {
  public:
    enum GameState { GOING, DRAW, WIN_O, WIN_X };
    enum Cell { O = 0, X = 1, FREE = 2 };

    Board(int _height = 10, int _width = 10, int _winLength = 5);

    void move(int x, int y, int sign); //сделать ход
    bool canMove(int x, int y) const; //корректен ли ход
    GameState isWin(); // текущее состояние: играем дальше; ничья; 0 выиграли; X выиграли

    const std::vector<Cell>& operator[](int x);
    int getMoveNum();

    const int winLength;
    const int height, width; // first and second coordinate
  protected:
    bool isCell(int x, int y) const;
    int maxLength(int x, int y, std::pair<int, int> dir, Cell c);
    bool checkWin(int x, int y, Cell c);

    std::vector<std::vector<Cell>> board;
    int cellsUsed;
    int moveNum;
    GameState state;
};