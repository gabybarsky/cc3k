#include "board.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*
 * Constructor for Board. Default value of filename is ""
 */
Board::Board(string filename) : file(filename) {
    currentFloor = 0;
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
void Board::modifyLocation(int row, int col, char change) {
    stringstream iss;
    string newChar;
    iss << change;
    iss >> newChar; 
    map[currentFloor][row].replace(col, 1, newChar);
}

/*
 * Purpose: create a board from a file
 * Returns: Nothing
 */
void Board::createBoard() {
    ifstream *in = (file == "") ? NULL : new ifstream(file.c_str());
    if (in == NULL) return;
    string row;
    for(int floor = 0; floor < 5; floor++) {
        for(int i=0; i < 25; i++) {
            getline(*in, row);
            map[floor][i] = row;
        }
    }
    delete in;
}

/*
 * Purpose: print out the map grid
 * Returns: Nothing
 */
void Board::printBoard() {
    for(int i = 0; i < 25; i++) {
        cout << map[currentFloor][i] << endl;
    }
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
