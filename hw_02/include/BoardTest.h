#pragma once

#include "Test.h"
#include "Board.h"

class BoardTest : public Test {
  public:
    virtual void runAllTests();

    BoardTest();

  private:
    void testMove1();
    void testMove2();
    void testMove3();

    void testCanMove1();
    void testCanMove2();
    void testCanMove3();

    void testIsWin1();
    void testIsWin2();
    void testIsWin3();
    void testIsWin4();

    void testBoardConstructor1();
    void testBoardConstructor2();
    void testBoardConstructor3();
};