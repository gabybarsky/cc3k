#include "chamber.h"
#include <iostream>
#include "board.h"
#include <cstdlib>
using namespace std;

//#define DEBUG_CHAMBER_EDGE

/*
 *Constructor for Chamber
 */
Chamber::Chamber(int id, Board *board) : id(id), board(board) {
    switch(id) { //Determines which chamber is being constructed in order to intialize its boundaries
        case 0:						//Top left chamber
            topRow = 3;
            topCol = 3;
            width = 26;
            height = 4;
            break;
        case 1:						//Bottom left chamber
            topRow = 15;
            topCol = 4;
            width = 21;
            height = 7;
            break;
        case 2:						//Middle chamber
            topRow = 10;
            topCol = 38;
            width = 12;
            height = 3;
            break;
        case 3:						//Top right chamber
            topRow = 3;
            topCol = 39;
            width = 37;
            height = 10;
            break;
        case 4:						//Bottom right chamber
            topRow = 16;
            topCol = 37;
            width = 39;
            height = 6;
            break;
    }
    validTile = new bool*[width];	//Matrix whose positions are booleans that determine whether
    for(int i=0; i < width; i++) {  //the corresponding positions in the chamber are valid
        validTile[i] = new bool[height];
    }
    assignValids();					//Populates validTile with the intial state of the board
}

/*
 *Destructor for Chamber
 */
Chamber::~Chamber() {				//Deletes the array in each index of ValidTile, then deletes the
    for(int i=0; i < width; i++) {  //validTile array itself
        delete[] validTile[i];
    }
    delete[] validTile;
}

/*
 * Purpose: assign values to the validTile matrix
 * Returns: Nothing 
 */
void Chamber::assignValids() {
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            validTile[x][y] = true;
        }
    }

    switch(id) {
        case 3:
            for(int x = 0; x < 22; x++) {
                for(int y = 4; y < height; y++) {
                    validTile[x][y] = false;
                }
            }
            for(int x = 23; x < width; x++) {
                for(int y = 0; y < 2; y++) {
                    validTile[x][y] = false;
                }
            }
            for(int x = 31; x < width; x++) {
                validTile[x][2] = false;
            }
            for(int x = 34; x < width; x++) {
                validTile[x][3] = false;
            }
            break;
        case 4:
            for(int x = 0; x < 28; x++) {
                for(int y = 0; y < 3; y++) {
                    validTile[x][y] = false;
                }
            }
            break;
    }
}

/*
 * Purpose: Getter method for the chamber's leftmost column
 * Returns: topCol
 */
int Chamber::getTopCol() {
    return topCol;
}

/*
 * Purpose: Getter method for the chamber's top row
 * Returns: topRow
 */
int Chamber::getTopRow() {
    return topRow;
}

/*
 * Purpose: Getter method for the chamber's width
 * Returns: width
 */
int Chamber::getWidth() {
    return width;
}

/*
 * Purpose: Getter method for the chamber's height
 * Returns: height
 */
int Chamber::getHeight() {
    return height;
}

/*
 * Purpose: Allows us to determine whether or not a tile is valid
 * Returns: true if the tile specified by col, row is valid, false otherwise
 */
bool Chamber::isValidTile(int col, int row) {
    if(col < 0 || col >= width || row < 0 || row >= height) {
        return false;
    }
    return validTile[col][row];
}

/*
 * Purpose: ALlows us to set the validity of a tile when it changes due to an
 * object being added to or removed from it
 * Returns: Nothing
 */
void Chamber::setValid(int col, int row, bool valid) {
    validTile[col][row] = valid;
}

/* 
 * Purpose: Allows us to determine whether a tile on the board is within this
 * chamber
 * Returns: true if the tile specified by x, y is in this chamber, false
 * otherwise
 */
bool Chamber::isWithin(int x, int y) {
    if(x >= topCol && x <= topCol + width) {
        if(y >= topRow && y <= topRow + height) {
            return true;
        }
    }
    return false;
}

/*
 * Purpose: Allows us to randomly generate a position in the chamber
 * Returns: A vector of the randomly generated position
 */
vector<int> Chamber::generatePosition() {
    int x = rand() % width;
    int y = rand() % height;

    while(!isValidTile(x, y)) {
        x = rand() % width;
        y = rand() % height;
    }

    vector<int> pos;
    pos.push_back(x + topCol);
    pos.push_back(y + topRow);
    return pos;
}

/*
 * Purpose: Generates the stairs in this chamber
 * Returns: Nothing
 */
void Chamber::generateStairs() {
    vector<int> pos = generatePosition();
    setValid(pos[0] - topCol, pos[1] - topRow, false);
    board->modifyLocation(pos[0], pos[1], '\\');
} 

/* 
 * Purpose: Debugging method
 * Returns: Nothing
 */
void Chamber::generateChamber() {
#ifdef DEBUG_CHAMBER_EDGE
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if(isValidTile(x, y)) {
                board->modifyLocation(x + topCol, y + topRow, 'a');
            } 
        }
    }
#endif
} 
