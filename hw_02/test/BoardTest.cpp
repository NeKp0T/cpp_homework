#include "BoardTest.h"

BoardTest::BoardTest() {}

void BoardTest::runAllTests() {
    testBoardConstructor1();
    testBoardConstructor2();
    testBoardConstructor3();

    testMove1();
    testMove2();
    testMove3();

    testCanMove1();
    testCanMove2();
    testCanMove3();

    testIsWin1();
    testIsWin2();
    testIsWin3();
    testIsWin4();
}

void BoardTest::testBoardConstructor1() {
    Board b(1, 15, 9);
    DO_CHECK(b.height == 1);
    DO_CHECK(b.width == 15);
    DO_CHECK(b.winLength == 9);
}
void BoardTest::testBoardConstructor2() {
    Board b(15, 1, 1);
    DO_CHECK(b.height == 15);
    DO_CHECK(b.width == 1);
    DO_CHECK(b.winLength == 1);
}
void BoardTest::testBoardConstructor3() {
    Board b(100, 100, 5);
    DO_CHECK(b.height == 100);
    DO_CHECK(b.width == 100);
    DO_CHECK(b.winLength == 5);
}

void BoardTest::testMove1() {
    Board b;
    b.move(0, 0, 0);
    DO_CHECK(b[0][0] == Board::O);
}
void BoardTest::testMove2() {
    Board b;
    b.move(9, 9, 1);
    DO_CHECK(b[9][9] == Board::X);
}
void BoardTest::testMove3() {
    Board b(3, 3, 5);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!(i == 1 && j == 1))
                b.move(i, j, (i + j) % 2);
        }
    }
    DO_CHECK(b[1][1] == Board::FREE);
}

void BoardTest::testCanMove1() {
    Board b;
    b.move(9, 0, 0);
    DO_CHECK(b.canMove(9, 0) == false);
}
void BoardTest::testCanMove2() {
    Board b;
    b.move(0, 9, 0);
    DO_CHECK(b.canMove(9, 0) == true);
}
void BoardTest::testCanMove3() {
    Board b;
    DO_CHECK(b.canMove(10, 0) == false);
    DO_CHECK(b.canMove(0, 10) == false);
    DO_CHECK(b.canMove(-1, 0) == false);
    DO_CHECK(b.canMove(0, -1) == false);
}

void BoardTest::testIsWin1() {
    Board b(3, 3, 3);
    b.move(1, 1, 0);
    b.move(0, 0, 1);    // XO.
    b.move(0, 1, 0);    // XO.
    b.move(1, 0, 1);    // .O.
    b.move(2, 1, 0);
    DO_CHECK(b.isWin() == Board::WIN_O);
}
void BoardTest::testIsWin2() {
    Board b(3, 3, 3);
    b.move(1, 1, 0);
    b.move(0, 0, 1);    // XO.
    b.move(0, 1, 0);    // XO.
    b.move(2, 1, 1);    // OX.
    b.move(1, 0, 0);  
    DO_CHECK(b.isWin() == Board::GOING);
}
void BoardTest::testIsWin3() {
    Board b(9, 9, 10);
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++) {
            DO_CHECK(b.isWin() == Board::GOING);
            b.move(i, j, (i + j) % 2);
        }
    DO_CHECK(b.isWin() == Board::DRAW);
}
void BoardTest::testIsWin4() {
    Board b(3, 3, 3);
    b.move(1, 1, 1);
    b.move(0, 0, 1);
    b.move(2, 2, 1);
    DO_CHECK(b.isWin() == Board::WIN_X);
}