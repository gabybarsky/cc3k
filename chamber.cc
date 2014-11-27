#include "chamber.h"
#include "board.h"

Chamber::Chamber() {
    id = -1;
    floor = -1;
}

Chamber::Chamber(int id, int floor) : id(id), floor(floor) {
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

bool Chamber::isValidTile(int col, int row) {
    return validTile[col][row];
}

void Chamber::generateChamber(Board *board) {
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
