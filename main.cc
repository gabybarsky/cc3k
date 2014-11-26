#include "board.h"

int main() {
    Board *grid = new Board("grid.txt");
    //grid->modifyLocation(0, 0, 'a');
    //grid->modifyLocation(24, 78, 'c');
    grid->printBoard();
    return 0;
}
