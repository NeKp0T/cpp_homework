#include "BoardView.h"
#include <cstring>

int main(int argc, char **argv) {
    bool silent = false;
    if (argc > 2) {
        printf("Too many arguments\n");
        return 1;
    }
    if (argc == 2) {
        if (strcmp(argv[1], "silent") != 0) {
            printf("Unknown argument\n");
            return 2;
        }
        silent = true;
    }

    Board b;
    View v(b, silent);

    while (!v.isEnded()) {
        v.doGameCycle();
    }
}
