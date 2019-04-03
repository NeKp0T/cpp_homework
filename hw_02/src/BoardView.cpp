#include "BoardView.h"
#include <tuple>

View::View(Board &_board, bool _silent) : 
    board(_board), 
    silent(_silent), 
    gameEnded(false) {}

void View::doGameCycle() {
    int player = board.getMoveNum() % 2;
    if (!silent)
        showBoard();

    int x, y;
    std::tie(x, y) = getInput(player);
    if (x == -1 && y == -1) {
        gameEnded = true;
        return;
    }

    if (!silent)
        printf("\n");
        
    board.move(x, y, player);

    if (board.isWin() != Board::GOING) {
        gameEnded = true;
        showBoard();
        if (board.isWin() == Board::DRAW)
            printf("Draw.\n");
        else
            printf("%c wins!\n", signs[player]);
    }
}

std::pair<int, int> View::getInput(int player) {
    bool goodMove = false;
    int x, y;
    while (!goodMove)
    {
        std::printf("%c move: ", signs[player]);

        int read = std::scanf("%d %d", &x, &y);

        if (x == -1 && y == -1)
            break;

        if (read != 2 || !board.canMove(x, y))
            printf("Bad move!\n");
        else 
            goodMove = true;
    }
    return {x, y};
}

bool View::isEnded() {
    return gameEnded;
}

void View::showBoard() {
    static const char cellState[3] = { 'O', 'X', '.' };

    for (int x = 0; x < board.height; x++) {
        for (int y = 0; y < board.width; y++) {
            printf("%c", (int)cellState[board[x][y]]);
        }
        printf("\n");
    }
}
