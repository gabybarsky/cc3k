#include "chamber.h"
#include "board.h"
#include "players/shade.h"
#include "players/drow.h"
#include "players/goblin.h"
#include "players/vampire.h"
#include "players/troll.h"
#include <cstdlib>
using namespace std;

Chamber::Chamber(int id, int floor, Board* board) : id(id), floor(floor), board(board) {
    switch(id) {
        case 0:
            topRow = 3;
            topCol = 3;
            width = 26;
            height = 4;
            break;
        case 1:
            topRow = 15;
            topCol = 4;
            width = 21;
            height = 7;
            break;
        case 2:
            topRow = 3;
            topCol = 39;
            width = 37;
            height = 10;
            break;
        case 3:
            topRow = 10;
            topCol = 38;
            width = 12;
            height = 3;
            break;
        case 4:
            topRow = 16;
            topCol = 37;
            width = 39;
            height = 6;
            break;
    }
    validTile = new bool*[width];
    for(int i=0; i < width; i++) {
        validTile[i] = new bool[height];
    }
    assignValids();
}

Chamber::~Chamber() {
    for(int i=0; i < width; i++) {
        delete[] validTile[i];
    }
    delete[] validTile;
}

void Chamber::assignValids() {
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            validTile[x][y] = true;
        }
    }

    switch(id) {
        case 2:
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

int Chamber::getTopCol() {
    return topCol;
}

int Chamber::getTopRow() {
    return topRow;
}

int Chamber::getWidth() {
    return width;
}

int Chamber::getHeight() {
    return height;
}

bool Chamber::isValidTile(int col, int row) {
    return validTile[col][row];
}

void Chamber::generatePlayer(char race) {
    int x = rand() % width;
    int y = rand() % height;

    while(!isValidTile(x, y)) {
        x = rand() % width;
        y = rand() % height;
    }

    vector<int> pos = vector<int>(x, y);
    switch(race) {
        case 's': // shade
            board->player = new Shade(id, pos);
            break;
        case 'd': // drow
            board->player = new Drow(id, pos);
            break;
        case 'v': // vampire
            board->player = new Vampire(id, pos);
            break;
        case 't': // troll
            board->player = new Troll(id, pos);
            break;
        case 'g': // goblin
            board->player = new Goblin(id, pos);
            break;
    }

}
    
void Chamber::generateChamber() {
}
/*
void Chamber::generateChamber(Board *board) {
#ifdef DEBUG_CHAMBER_EDGE
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if(isValidTile(x, y)) {
                board->modifyLocation(x + topCol, y + topRow, floor, 'a');
            } 
        }
    }
#endif
}*/
