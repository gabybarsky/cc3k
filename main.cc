#include "board.h"
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

void printBeginning() {
    cout << endl <<
"Welcome to CHAMBER CRAWLER 3000!!!\n\
This incredible version of the game is\n\
brought to you by: Gabriel Barsky, Nick White,\n\
AND CS246. We hope you enjoy.\n\n\
The commands are as follows:\n\
Movement: (no,so,ea,we,nw,ne,sw,se)\n\
Attack: a + direction\n\
Potion: u + direction\n\
For Attack and Potion you must be within 1 tile\n\
Restart: r" << endl << endl;
}

int main() {
    srand(time(NULL));
    printBeginning();
    Board *grid = new Board("grid.txt");
    //grid->modifyLocation(0, 0, 'a');
    //grid->modifyLocation(77, 24, 0, 'c');
    grid->printBoard();

    string c;
    cin >> c;
    while(!cin.eof()) {
        grid->updateBoard(c);
        grid->printBoard();
        cin >> c;
    }
    return 0;
}
