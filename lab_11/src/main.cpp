#include "employees.h"
#include <iostream>
#include <fstream>
#include <string>

int main() {
    EmployeesArray ea;
    std::string command;

    while (true) {
        std::cin >> command;

        if (command == "load") {
            std::string filename;
            std::cin >> filename;
            std::ifstream fin(filename, std::ios_base::binary);
            ea.add_read_binary(fin);
        }
        else if (command == "list") {
            std::cout << ea;
        }
        else if (command == "add") {
            ea.add_read(std::cin);
        }
        else if (command == "save") {
            std::string filename;
            std::cin >> filename;
            std::ofstream fout(filename, std::ios_base::binary);
            ea.write_binary(fout);
        }
        else if (command == "exit") {
            break;
        }
    }

    return 0;
}