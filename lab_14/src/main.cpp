#include "matrix.h"
#include <iostream>
#include <fstream>
#include <string>

unsigned int readReg() {
    char c;
    std::cin >> c;
    unsigned int r;
    std::cin >> r;
    return r;
}

int main() {
    Matrix reg[10];

    std::string command;
    while (std::cin >> command) {
        if (command == "load") {
            int r = readReg();
            std::string fname;
            std::cin >> fname;
            std::ifstream fin(fname);
            reg[r] = Matrix(fin);
        }

        if (command == "print") {
            std::cout << reg[readReg()];
        }

        if (command == "add") {
            int r1 = readReg();
            int r2 = readReg();
            try {
                reg[r1] += reg[r2];
            } catch (MatrixException &e) {
                std::cout << e.what() << std::endl;
            }
        }

        if (command == "mul" || command == "mult") {
            int r1 = readReg();
            int r2 = readReg();
            try {
                reg[r1] *= reg[r2];
            } catch (MatrixException &e) {
                std::cout << e.what() << std::endl;
            }
        }

        if (command == "elem") {
            int r1 = readReg();
            std::size_t x, y;
            std::cin >> x >> y;
            try {
                std::cout << reg[r1].get(x, y) << std::endl;
            } catch (MatrixException &e) {
                std::cout << e.what() << std::endl;
            }
        }

        if (command == "exit")
            return 0;
    }

    return 0;
}