#include "board.h"
#include "chamber.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

/*
 * Constructor for Board. Default value of filename is ""
 */
Board::Board(string filename) : file(filename) {
    player = NULL;
    currentFloor = 0;
    chambers = new Chamber*[5];
    map = new string*[5];
    for(int floor = 0; floor < 5; floor++) {
        map[floor] = new string[25];
    }
    createBoard();
}

/*
 * Destructor of a Board.
 */
Board::~Board() {
    for(int i = 0; i < 5; i++) {
        delete[] map[i];
    }
    delete[] map;
}

/*
 * Prupose: modify a certain character in the Board.
 *          map[row][column] gets changed to the new char change
 * Returns: Nothing
 */
void Board::modifyLocation(int col, int row, int floor, char change) {
    stringstream iss;
    string newChar;
    iss << change;
    iss >> newChar; 
    map[floor][row].replace(col, 1, newChar);
}

/*
 * Purpose: create a board from a file
 * Returns: Nothing
 */
void Board::createBoard() {
    ifstream *in = (file == "") ? new ifstream("grid.txt") 
                                : new ifstream(file.c_str());
    string row;
    for(int floor = 0; floor < 5; floor++) {
        for(int i=0; i < 25; i++) {
            getline(*in, row);
            map[floor][i] = row;
        }
        generateFloor(floor);
    }

    char character = playerSelect();
    int temp = rand() % 5;
    chambers[temp]->generatePlayer(character);
    delete in;
}

char Board::playerSelect() {
    char character; 
    cout << "Please select a race for your player: " << endl;
    cout << "   Drow: 'd', Goblin: 'g', Shade: 's', Troll: 't', Vampire: 'v'" << endl;
    cin >> character;
    while (character != 'd' && character != 'g' && character != 's'
            && character != 't' && character != 'v') {
        cout << "Invalid Selection. Please try again with one of \
the above selections (d, g, s, t, v):" << endl;
        cin >> character;
    }
    return character;
}

void Board::generateFloor(int floor) {
    for(int ch = 0; ch < 5; ch++) {
        chambers[ch] = new Chamber(ch, floor, this);
        chambers[ch]->generateChamber();
    }
}

/*
 * Purpose: print out the map grid
 * Returns: Nothing
 */
void Board::printBoard() {
    for(int i = 0; i < 25; i++) {
        cout << map[currentFloor][i] << endl;
    }
    cout << left << "Race: " << left << player->getRace();
    cout.width(70 - player->getRace().length() - 1);
    cout << right << "Floor: " << right << player->getFloor() + 1 << endl;

    cout << left;
    cout << "HP: " << player->getHp() << endl;
    cout << "Atk: " << player->getAtk() << endl;
    cout << "Def: " << player->getDef() << endl;
    cout << "Action: " << player->getAction() << endl;
}

/*
 * Purpose: find the character at a specific row and
 *          column of the board
 * Returns: char at map[row][col]
 */
char Board::getLocation(int row, int col) {
    string retRow = map[currentFloor][row];
    return retRow[col];
}

/*
 * Purpose: move up a floor
 * Returns: Nothing
 */
void Board::moveFloor() {
    currentFloor++;
}

/*
 * Purpose: Get the current Floor
 * Returns: integer currentFloor + 1
 */
int Board::getCurrentFloor() {
    return currentFloor + 1;
}
