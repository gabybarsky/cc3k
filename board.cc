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
        generateChambers(floor);
    }

    char character = playerSelect();
    int temp = rand() % 5;
    chambers[temp]->generatePlayer(character);
    
    for(int floor = 0; floor < 5; floor++) {
        generateFloor(floor);
    }
    delete in;
}

char Board::playerSelect() {
    char character; 
    cout << "Please select a race for your player: " << endl;
    cout << "   Drow: 'd', Goblin: 'g', Shade: 's', Troll: 't', Vampire: 'v'" << endl;
    cin >> character;
    while (character != 'd' && character != 'g' && character != 's'
            && character != 't' && character != 'v') {
        cout << "Invalid Selection. Please try again with one of"; 
        cout << " the above selections (d, g, s, t, v): ";
        cin >> character;
    }
    return character;
}

void Board::generateChambers(int floor) {
    for(int ch = 0; ch < 5; ch++) {
        chambers[ch] = new Chamber(ch, floor, this);
        chambers[ch]->generateChamber();
    }
}

void Board::generateFloor(int floor) {
    int random = rand() % 5;
    while(player->getChamber() == random) {
        random = rand() % 5;
    }
    chambers[random]->generateStairs(floor);
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
char Board::getLocation(int col, int row) {
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

void Board::makePlayer() {
    vector<int> pos = player->getPosition();
    modifyLocation(pos[0], pos[1], currentFloor, player->getSymbol());
}

void Board::updatePlayer(string direction) {
    vector<int> prevPos = player->getPosition();
    player->move(direction);
    vector<int> newPos = player->getPosition();
    char moveTile = getLocation(newPos[0], newPos[1]);

    if(moveTile == '|' || moveTile == '-') {
        player->setPosition(prevPos);
        player->addAction(" and hits his head on a wall!");
    } else if (moveTile == '+') {
        commitMove(moveTile, prevPos, newPos);

    } else if (moveTile == '#') {
        commitMove(moveTile, prevPos, newPos);

    } else if (moveTile == '\\') {
        moveFloor();
    } else if (moveTile == ' ') {
        player->setPosition(prevPos);
        player->addAction(" and almost falls into the void.");

    } else if(moveTile == '.') {
        if (player->getPrevTile() == '+') {
            modifyChamber(newPos);
        }
        Chamber *curChamber = chambers[player->getChamber()]; 
        if(curChamber->isValidTile(newPos[0] - curChamber->getTopCol(),
                    newPos[1] - curChamber->getTopRow())) {
            commitMove(moveTile, prevPos, newPos);
        } else {
            player->setPosition(prevPos);
            if(moveTile == 'H' || moveTile == 'D' || moveTile == 'E' ||
                    moveTile == 'O' || moveTile == 'M' || moveTile == 'D') {
                player->addAction(" and walks straight into an Enemy! OH NOES!");
            } else if(moveTile == 'P') {
                player->setPosition(prevPos);
                player->addAction(" but there seems to be a Potion there!");
            }
        }
    }
}

void Board::commitMove(char moveTile, vector<int> prevPos, vector<int> newPos) {
    modifyLocation(prevPos[0], prevPos[1], currentFloor, player->getPrevTile());
    player->setPrevTile(moveTile);
    modifyLocation(newPos[0], newPos[1], currentFloor, player->getSymbol());
}

void Board::modifyChamber(vector<int> newPos) {
    for(int i = 0; i < 5; i++) {
        if(chambers[i]->isWithin(newPos[0], newPos[1])) {
            player->setChamber(i);
            return;
        }
    }
    cerr << "ERROR: Unkown Chamber" << endl;
}

