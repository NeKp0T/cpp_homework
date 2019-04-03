#pragma once

#include "Board.h"
#include <cstdio>

const char signs[2] = {'O', 'X'};

class View {
  public:
    View(Board &_board, bool _silent = false);
    void showBoard();   //вывод доски на экран
    void doGameCycle(); //основной цикл игры: ввод хода, вывод на экран доски, проверка текущего состояния
    bool isEnded();

  protected:
    Board &board;
    bool silent;

    bool gameEnded;

    std::pair<int, int> getInput(int player);
};