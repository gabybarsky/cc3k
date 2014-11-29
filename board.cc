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
    chambers = new Chamber*[5];
    map = new string[25];
	potions = new Potion*[10];
	goldPiles = new Gold*[10];
	enemies = new Enemy*[20];
    createBoard();
    createPlayer();
}

/*
 * Destructor of a Board.
 */
Board::~Board() {
    cleanBoard();
    delete[] map;
    delete[] chambers;
    delete[] potions;
	delete[] goldPiles;
    delete[] enemies;
}

/*
 * Purpose: modify a certain character in the Board.
 *          map[row][column] gets changed to the new char change
 * Returns: Nothing
 */
void Board::modifyLocation(int col, int row, char change) {
    stringstream iss;
    string newChar;
    iss << change;
    iss >> newChar; 
    map[row].replace(col, 1, newChar);
}

/* TODO: Does a file indicate all 5 floors? Or just 1
 * Purpose: create a board from a file
 * Returns: Nothing
 */
void Board::createBoard() {
    ifstream *in = (file == "") ? new ifstream("grid.txt") 
        : new ifstream(file.c_str());
    string row;
    for(int i=0; i < 25; i++) {
        getline(*in, row);
        map[i] = row;
    }
    generateChambers();
	generatePotions();
	generateGold();
	generateEnemies();
    delete in;
}

void Board::createPlayer() {
    char character = playerSelect();
    int temp = rand() % 5;
    chambers[temp]->generatePlayer(character);

    generateFloor();
}

void Board::cleanBoard() {
    for(int i = 0; i < 5; i++) {
        delete chambers[i];
    }
    for(int i = 0; i < 10; i++) {
        delete potions[i];
    }
    for(int i = 0; i < 20; i++) {
        delete enemies[i];
    }
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

void Board::generateChambers() {
    for(int ch = 0; ch < 5; ch++) {
        chambers[ch] = new Chamber(ch, this);
        chambers[ch]->generateChamber();
    }
}

void Board::generateFloor() {
    int random = rand() % 5;
    while(player->getChamber() == random) {
        random = rand() % 5;
    }
    chambers[random]->generateStairs();
}
/*
 * Purpose: print out the map grid
 * Returns: Nothing
 */
void Board::printBoard() {
    for(int i = 0; i < 25; i++) {
        cout << map[i] << endl;
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
    return map[row][col];
}

/*
 * Purpose: move up a floor
 * Returns: Nothing
 */
void Board::moveFloor() {
    cleanBoard();
    createBoard();

    int random = rand() % 5;
    player->upFloor();
    vector<int> playerPos = chambers[random]->generatePosition();
    player->setPosition(playerPos);
    player->setChamber(random);

    generateFloor();
    insertPlayer();
}

void Board::insertPlayer() {
    vector<int> pos = player->getPosition();
    modifyLocation(pos[0], pos[1], player->getSymbol());
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
        if (player->getChamber() != -1) {
            Chamber *ch = chambers[player->getChamber()];
            ch->setValid(prevPos[0] - ch->getTopCol(), prevPos[1] - ch->getTopRow(), true);
        }
        player->setChamber(-1);

    } else if (moveTile == '#') {
        commitMove(moveTile, prevPos, newPos);

    } else if (moveTile == '\\') {
        player->setPrevTile('.');
        moveFloor();
    } else if (moveTile == ' ') {
        player->setPosition(prevPos);
        player->addAction(" and almost falls into the void.");

    } else if(moveTile == '.') {
        if (player->getPrevTile() == '+') {
            modifyChamber(newPos);
        }
        Chamber *ch = chambers[player->getChamber()]; 
        int topCol = ch->getTopCol();
        int topRow = ch->getTopRow();
        if(ch->isValidTile(newPos[0] - topCol, newPos[1] - topRow)) {
            if(player->getPrevTile() != '+') {
                ch->setValid(prevPos[0] - topCol, prevPos[1] - topRow, true);
            }
            ch->setValid(newPos[0] - topCol, newPos[1] - topRow, false);
            commitMove(moveTile, prevPos, newPos);
        } else {
            player->setPosition(prevPos);
            player->addAction(" OH NO WHATS GOING ON THERES A GHOST!");
        }
    } else if(moveTile == 'H' || moveTile == 'W' || moveTile == 'E' ||
            moveTile == 'O' || moveTile == 'M' || moveTile == 'D' || moveTile == 'L') {
        player->setPosition(prevPos);
        player->addAction(" and walks straight into an Enemy! OH NOES!");
    } else if(moveTile == 'P') {
        player->setPosition(prevPos);
        player->addAction(" but there seems to be a Potion there!");
    }
}

void Board::commitMove(char moveTile, vector<int> prevPos, vector<int> newPos) {
    modifyLocation(prevPos[0], prevPos[1], player->getPrevTile());
    player->setPrevTile(moveTile);
    modifyLocation(newPos[0], newPos[1], player->getSymbol());
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

Enemy* Board::generateHuman() {
    int random = rand() % 5;
    vector<int> position = chambers[random]->generatePosition();
    Enemy *e = new Human(true, random, position);
    return e;
}

Enemy* Board::generateDwarf() {
    int random = rand() % 5;
    vector<int> position = chambers[random]->generatePosition();
    Enemy *e = new Dwarf(true, random, position);
    return e;
}

Enemy* Board::generateHalfling() {
    int random = rand() % 5;
    vector<int> position = chambers[random]->generatePosition();
    Enemy *e = new Halfling(true, random, position);
    return e;
}

Enemy* Board::generateElf() {
    int random = rand() % 5;
    vector<int> position = chambers[random]->generatePosition();
    Enemy *e = new Halfling(true, random, position);
    return e;
}

Enemy* Board::generateMerchant() {
    int random = rand() % 5;
    vector<int> position = chambers[random]->generatePosition();
    Enemy *e = new Merchant(false, random, position);
    return e;
}

Enemy* Board::generateOrc() {
    int random = rand() % 5;
    vector<int> position = chambers[random]->generatePosition();
    Enemy *e = new Orc(true, random, position);
    return e;
}

vector<int> Board::generateDragonPos(vector<int> pos) {
	int x = rand() % 2 - 1;
	int y = rand() % 2 - 1;
	while(x == 0 && y == 0) {
		x = rand() % 2 - 1;
		y = rand() % 2 - 1;
	}
	vector<int> position = pos;
	position[0] += x;
	position[1] += y;
	return position;
}

void Board::generateEnemies() {
    for(int i=0; i<20; i++) {
        int random = rand() % 18;
        if(random <= 3)
            enemies[i] = generateHuman();
        else if(random <= 6)
            enemies[i] = generateDwarf();
        else if(random <= 11)
            enemies[i] = generateHalfling();
        else if(random <= 13)
            enemies[i] = generateElf();
        else if(random <= 15)
            enemies[i] = generateMerchant();
        else if(random <=17)
            enemies[i] = generateOrc();
        else
            cerr<<"I don't know how random works"<<endl;
        vector<int> pos = enemies[i]->getPosition();
        modifyLocation(pos[0], pos[1], enemies[i]->getSymbol());
        Chamber *ch = chambers[enemies[i]->getChamber()];
        ch->setValid(pos[0] - ch->getTopCol(), pos[1] - ch->getTopRow(), false);
    }
}

void Board::generatePotions() {
    for(int i=0; i<10; i++) {
        int chamber = rand() % 5;
        int pot = rand() % 6;
        string type = "";
        vector<int> position = chambers[chamber]->generatePosition();
        switch(pot) {
            case 0:
                type = "RH";
                break;
            case 1:
                type = "BA";
                break;
            case 2:
                type = "BD";
                break;
            case 3:
                type = "PH";
                break;
            case 4:
                type = "WA";
                break;
            case 5:
                type = "WD";
                break;
            default:
                cerr<<"I don't know how random works"<<endl;
        }
        potions[i] = new Potion(type, position);
        modifyLocation(potions[i]->getPosition()[0], potions[i]->getPosition()[1], 'P');
        Chamber *ch = chambers[chamber];
        ch->setValid(position[0] - ch->getTopCol(), position[1] - ch->getTopRow(), false);
    }
}

void Board::generateGold() {
	for(int i = 0; i < 10; i++) {
		int chamber = rand() % 5;
		int random = rand() % 8;
		vector<int> position = chambers[chamber]->generatePosition();
		if(random <= 4)
			goldPiles[i] = new Gold(position, 2);
		else if(random <= 6)
			goldPiles[i] = new Gold(position, 1);
		else if(random == 7) {
			goldPiles[i] = new Gold(position, 6);
			vector<int> dragonPosition = generateDragonPos(position);
			dragons.push_back(new Dragon(true, chamber, dragonPosition, goldPiles[i]));
			modifyLocation(dragonPosition[0], dragonPosition[1], 'D');
		}
		modifyLocation(goldPiles[i]->getPosition()[0], goldPiles[i]->getPosition()[1], 'G');
	}
}
