#include "board.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

/*
 * Constructor for Board. Default value of filename is ""
 */
Board::Board(string filename) : file(filename) {
    map = new string[25];
    createBoard();
}

/*
 * Destructor of a Board.
 */
Board::~Board() {
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
    map[row].replace(col, 1, newChar);
}

/*
 * Purpose: create a board from a file
 * Returns: Nothing
 */
void Board::createBoard() {
    ifstream *in = (file == "") ? NULL : new ifstream(file.c_str());
    if (in == NULL) return;
    string row;
    for(int i=0; i < 25; i++) {
        getline(*in, row);
        map[i] = row;
    }
    delete in;
}

/*
 * Purpose: print out the map grid
 * Returns: Nothing
 */
void Board::printBoard() {
    for(int i = 0; i < 25; i++) {
        cout << map[i] << endl;
    }
}

/*
 * Purpose: find the character at a specific row and
 *          column of the board
 * Returns: char at map[row][col]
 */
char Board::getLocation(int row, int col) {
    string retRow = map[row];
    return retRow[col];
}
