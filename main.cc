#include "board.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    Board *grid = new Board("grid.txt");
    //grid->modifyLocation(0, 0, 'a');
    //grid->modifyLocation(77, 24, 0, 'c');
    grid->printBoard();

    string c;
    cin >> c;
    while(!cin.eof()) {
        grid->player->move(c);
        grid->printBoard();
        cin >> c;
    }
    return 0;
}
