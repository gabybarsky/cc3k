#include "board.h"

int main() {
    Board *grid = new Board("grid.txt");
    //grid->modifyLocation(0, 0, 'a');
    //grid->modifyLocation(77, 24, 0, 'c');
    grid->printBoard();
    return 0;
}
