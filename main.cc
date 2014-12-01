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

void win() {
    cout << endl <<
"CONGRATULATIONS!\n\
You have successfully made it through the dungeon.\n\
Player, you are the new supreme overlord of the dungeon.\n\
Be good to the civilians, they didn't mean to attack you all the time.\n\
(Yes they did, but they didn't have control over it).\n\
Your gold will be shipped to your home address in 5-10 business days." << endl;
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

        if(grid->hasWon()) {
            win();
            break;
        }
        grid->printBoard();
        cin >> c;
    }

    delete grid;
    return 0;
}
