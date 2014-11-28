#include "board.h"
#include <iostream>
#include <string>
using namespace std;

void printBeginning() {
    cout << endl <<
"Welcome to CHAMBER CRAWLER 3000!!!\n\
This incredible version of the game is\n\
brought to you by: Gabriel Barsky, Nick White,\n\
AND CS246. We hope you enjoy." << endl << endl;
}

int main() {
    printBeginning();
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
