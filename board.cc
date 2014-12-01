#include "board.h"
#include "chamber.h"
#include "players/shade.h"
#include "players/drow.h"
#include "players/goblin.h"
#include "players/vampire.h"
#include "players/troll.h"
#include "enemies/dwarf.h"
#include "enemies/elf.h"
#include "enemies/halfling.h"
#include "enemies/human.h"
#include "enemies/merchant.h"
#include "enemies/orc.h"
#include "enemies/dragon.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

/*
 * Constructor for Board. Default value of filename is ""
 * Create empty arrays for all necessary objects
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
    if(player != NULL) {
        delete player;
    }
}

/*
 * Purpose: Determine if game is won
 * Returns: true if top floor (6), false otherwise
 */
bool Board::hasWon() {
    if (player->getFloor() == 5) {
        return true;
    }
    return false;
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

/*
 * Purpose: Create a player character based on user input
 *          Randomize chamber location of player and then generate the floor
 * Returns: Nothing
 */
void Board::createPlayer() {
    char race = playerSelect();
    int id = rand() % 5;
    Chamber *ch = chambers[id];
    vector<int> pos = ch->generatePosition();
    ch->setValid(pos[0] - ch->getTopCol(), pos[1] - ch->getTopRow(), false);

    switch(race) {
        case 's': // shade
            player = new Shade(id, pos, this); break;
        case 'd': // drow
            player = new Drow(id, pos, this); break;
        case 'v': // vampire
            player = new Vampire(id, pos, this); break;
        case 't': // troll
            player = new Troll(id, pos, this); break;
        case 'g': // goblin
            player = new Goblin(id, pos, this); break;
    }
    insertPlayer();
    generateFloor();
}

/*
 * Purpose: Clean all object arrays on Board to reuse for new floors
 *          or to aid destruction of the Board
 * Returns: Nothing
 */
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
    for(int i = 0; i < 10; i++) {
        delete goldPiles[i];
    }
    for(int i = 0; i < dragons.size(); i++) {
        delete dragons[i];
    }
}

void Board::resetGame() {
    cleanBoard();
    if (player != NULL) {
        delete player;
    }
    createBoard();
    createPlayer();
}

/*
 * Purpose: Get user input on PC race that they would like
 * Returns: char representing the character race
 */
char Board::playerSelect() {
    char character; 
    cout << "Please select a race for your player: " << endl;
    cout << "   Drow: 'd', Goblin: 'g', Shade: 's', Troll: 't', Vampire: 'v'" << endl;
    cin >> character;
    while (character != 'd' && character != 'g' && character != 's'
            && character != 't' && character != 'v') {
        if (character == 'r') {
            resetGame();
            return ' ';
        }
        cout << "Invalid Selection. Please try again with one of"; 
        cout << " the above selections (d, g, s, t, v): ";
        cin >> character;
    }
    return character;
}

/*
 * Purpose: create the chambers on the currentFloor
 * Returns: Nothing
 */
void Board::generateChambers() {
    for(int ch = 0; ch < 5; ch++) {
        chambers[ch] = new Chamber(ch, this);
        chambers[ch]->generateChamber();
    }
}

/*
 * Purpose: generate the stairs on the floor
 * Returns: Nothing
 */
void Board::generateFloor() {
    int random = rand() % 5;
    while(player->getChamber() == random) {
        random = rand() % 5;
    }
    chambers[random]->generateStairs();
}

/*
 * Purpose: print out the map grid
 *          and stats of player
 * Returns: Nothing
 */
void Board::printBoard() {
    for(int i = 0; i < 25; i++) {
        cout << map[i] << endl;
    }
    cout << "Race: " << player->getRace();
    cout << " Gold: " << player->getGoldStr();
    cout.width(63 - player->getRace().length() - player->getGoldStr().length() - 1);
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
 * Purpose: move up a floor, clean last floor and create a new one
 * Returns: Nothing
 */
void Board::moveFloor() {
    cleanBoard();
    createBoard();

    int random = rand() % 5;
    player->upFloor(random);

    generateFloor();
    insertPlayer();
}

/*
 * Purpose: Generate position within chamber
 * Returns: vector position
 */
vector<int> Board::generatePosition(int chamber) {
    return chambers[chamber]->generatePosition();
}

/*
 * Purpose: insert a player character into the map
 * Returns: Nothing
 */
void Board::insertPlayer() {
    vector<int> pos = player->getPosition();
    modifyLocation(pos[0], pos[1], player->getSymbol());
}

/*
 * Purpose: check if tile is valid in chamber
 * Returns: true if it is, false otherwise
 */
bool Board::isValidTile(int chamber, int col, int row) {
    Chamber *ch = chambers[chamber];
    return ch->isValidTile(col - ch->getTopCol(), row - ch->getTopRow());
}

/*
 * Purpose: get the name of the specific potion
 * Returns: string name
 */
string Board::getPotionName(vector<int> position) {
    for(int i = 0; i < 10; i++) {
        if(potions[i]->getPosition() == position) {
            return potions[i]->getName();
        }
    }
    return NULL;
}

/*
 * Purpose: update the Board
 * Returns: Nothing
 */
void Board::updateBoard(string direction) {
    if (direction == "r") {
        resetGame();
        return;
    }
    //TODO: handle attacking before all this
    updatePlayer(direction); //TODO: make this method ONLY move the character
	if(player->getRace() == "Troll")
		player->addHp(10);
    updateEnemies();
}

/*
 * Purpose: update and move all alive enemies
 * Returns: nothing
 */
void Board::updateEnemies() {
    for(int i=0; i < 20; i++) {
        if(enemies[i]->getHp() > 0) {
		    if(player->isNearby(enemies[i]) && enemies[i]->isHostile()) { 
			    int result = enemies[i]->attack(player);
			    if(result == 1) { //Player died
				    printBoard();
				    resetGame();
				    return;	
			    }
		    }
            else if(getLocation(enemies[i]->getPosition()[0], enemies[i]->getPosition()[1]) != '.') {
                enemies[i]->move();
            }
        }
    }
}

/*
 * Purpose: update a players position in the map. Check for collisions
 *          and obstacles in way as well as interaction with other objects
 * Returns: Nothing
 */
void Board::updatePlayer(string direction) {
    bool usePotion = false;
    bool attack = false;
    if (direction[0] == 'u') {
        usePotion = true;
        direction.erase(0, 1);
    } else if (direction[0] == 'a') {
        attack = true;
        direction.erase(0, 1);
    }
    vector<int> prevPos = player->getPosition(); // store previous position for reference
    if(usePotion || attack) {
        player->changePosition(direction);
    } else {
        player->move(direction);
    }
    vector<int> newPos = player->getPosition(); // store new position for reference
    char moveTile = getLocation(newPos[0], newPos[1]); // get the tile player moves to

    if(usePotion || attack) {
        player->setPosition(prevPos);
    }

    // if potion command and no potion in the direction
    if(usePotion && moveTile != 'P') {
        player->setAction("PC tries to use Potion but there is no Potion around! ");

        // if attack command but no enemy in the direction
    } else if(attack) { 
        if(moveTile != 'H' && moveTile != 'W' && moveTile != 'E' &&
                moveTile != 'O' && moveTile != 'M' && moveTile != 'L') {
            player->setAction("PC tries to attack but there is no Enemy around! ");
        } else {
            for(int i = 0; i < 20; i++) {
                if(enemies[i]->getPosition() == newPos && enemies[i]->getHp() > 0) {
                    int result = player->attack(enemies[i]);
					int gold = 0;
                    if(enemies[i]->getRace()=="Merchant")
                        makeMerchantsHostile();
                    if(result == 1) { //Enemy died
                        if(enemies[i]->getRace() == "Human") {
							gold += 4;
                        } else if(enemies[i]->getRace() != "Dragon") {
                            gold += rand() % 2 + 1;
                        }
						if(player->getRace() == "Goblin") {
							gold += 5;
						}
						player->addGold(gold);
                        modifyLocation(newPos[0], newPos[1], '.');
                        validateTile(true, newPos, player->getChamber());
                    }
                }
            }
            attack = false;
        }
    } else if(moveTile == 'P' && usePotion) {
        for(int i = 0; i < 10; i++) {
            if(potions[i]->getPosition() == newPos) {
                // found potion in array. No need to delete the memory allocation.
                // Refer to gold pickup for more info
                player->setAction("PC uses " + potions[i]->getName());
                potions[i]->use(*player);
                player->learnPotion(potions[i]->getName());
                modifyLocation(newPos[0], newPos[1], '.');
                validateTile(true, newPos, player->getChamber());
            }
        }
    }
}

bool Board::pickupGold(vector<int> position) {
    for(int i = 0; i < 10; i++) {
        if(goldPiles[i]->getPosition() == position) {
            // found gold piece in array. No need to delete the memory allocation
            // since tile will no longer display 'G' and therefore no duplicate
            // gold will be grabbed. Deletion can be done in cleanup
            if(!goldPiles[i]->isAvailable()) {
                player->addAction("But the dragon protects its gold. ");
                return false;
            }
            int quantity = goldPiles[i]->getQuantity();
            player->addGold(quantity);
            stringstream actionStream;
            actionStream << "He finds " << quantity << ((quantity == 1) ? " piece" : " pieces") << " of gold!";
            player->addAction(actionStream.str());
            return true;
        }
    }
    cerr << "ERROR: [Board::pickupGold]: Unkown Gold Piece" << endl;
    return true;
}

/*
 * Purpose: set the chambers tile at pos to bool valid
 * Returns: Nothing
 */
void Board::validateTile(bool valid, vector<int> pos, int chamber) {
    Chamber *ch = chambers[chamber];
    ch->setValid(pos[0] - ch->getTopCol(), pos[1] - ch->getTopRow(), valid);
}

/*
 * Purpose: commit the movement of the character. Modify map locations of prevPos
 *          and newPos to desired tiles and set players new previous tile
 * Returns: Nothing
 */
void Board::commitMove(char moveTile, vector<int> prevPos, vector<int> newPos, Character *c) {
    modifyLocation(prevPos[0], prevPos[1], c->getPrevTile());
    c->setPrevTile(moveTile);
    modifyLocation(newPos[0], newPos[1], c->getSymbol());
}

/*
 * Purpose: find the new chamber corresponding to the newPos of the player.
 *          set players chamber field to the new chamber
 * Returns: Nothing
 */
void Board::modifyChamber(vector<int> newPos) {
    for(int i = 0; i < 5; i++) {
        if(chambers[i]->isWithin(newPos[0], newPos[1])) {
            player->setChamber(i);
            return;
        }
    }
    // should NEVER arrive at this spot.
    cerr << "ERROR: [Board::modifyChamber(vector<int>)]: Unkown Chamber" << endl;
}

/*
 * Purpose: generate the position relative to a given pos
 *          in chamber. if canBeSame is true the new position
 *          can be the same as the given pos
 * Returns: vector<int> position 
 */
vector<int> Board::generateNearbyPos(vector<int> pos, int chamber, bool canBeSame) {
    // random x and y each between -1 and 1
    int x = rand() % 3 - 1;
    int y = rand() % 3 - 1;
    // make sure x and y are not BOTH 0 AND the pos is valid
    Chamber *ch = chambers[chamber];
    int col = ch->getTopCol();
    int row = ch->getTopRow();
    while((!canBeSame && x == 0 && y == 0) || 
            !(ch->isValidTile(pos[0] + x - col, pos[1] + y - row))) {
        x = rand() % 3 - 1;
        y = rand() % 3 - 1;
    }
    vector<int> position = pos;
    position[0] += x;
    position[1] += y;
    return position;
}

/*
 * Purpose: generate the Enemy of type race
 * Returns: Nothing
 */
Enemy *Board::generateEnemy(char race) {
    int random = rand() % 5;
    vector<int> position = chambers[random]->generatePosition();
    Enemy *e;
    switch (race) {
        case 'H':
            e = new Human(true, random, position, this); break;
        case 'W':
            e = new Dwarf(true, random, position, this); break;
        case 'L':
            e = new Halfling(true, random, position, this); break;
        case 'E':
            e = new Elf(true, random, position, this); break;
        case 'M':
            e = new Merchant(false, random, position, this); break;
        case 'O':
            e = new Orc(true, random, position, this); break;
        default:
            // should never hit this
            cerr << "ERROR [Board::generateEnemy]: Unknown Enemy" << endl;
            return NULL;
    }
    return e;
}

/*
 * Purpose: generate all 20 enemies on the floor
 * Returns: Nothing
 */
void Board::generateEnemies() {
    for(int i=0; i<20; i++) {
        /* random probabilities of an enemy spawn
         *      Human:      2/9
         *      Dwarf:      3/18
         *      Halfling:   5/18
         *      Elf:        1/9
         *      Orc:        1/9
         *      Merchant:   1/9
         */
        int random = rand() % 18;
        char race = '~';
        if(random <= 3)
            race = 'H';
        else if(random <= 6)
            race = 'W';
        else if(random <= 11)
            race = 'L';
        else if(random <= 13)
            race = 'E';
        else if(random <= 15)
            race = 'O';
        else if(random <=17)
            race = 'M';
        else
            // should NEVER reach this piece
            cerr<<"ERROR: [Board::generateEnemies()]: Unkown Random selection."<<endl;

        enemies[i] = generateEnemy(race);
        // add enemy symbol to the map and invalidate its position in the chamber
        vector<int> pos = enemies[i]->getPosition();
        modifyLocation(pos[0], pos[1], enemies[i]->getSymbol());
        Chamber *ch = chambers[enemies[i]->getChamber()];
        ch->setValid(pos[0] - ch->getTopCol(), pos[1] - ch->getTopRow(), false);
    }
}

/*
 * Purpose: generate the 10 potions on the board
 * Returns: Nothing
 */
void Board::generatePotions() {
    for(int i=0; i<10; i++) {
        // randomize chamber and potion type. All potions have equal probability
        int chamber = rand() % 5;
        int pot = rand() % 6;
        string type = "";
        // generate random position in chamber
        vector<int> position = chambers[chamber]->generatePosition();
        switch(pot) {
            case 0:
                type = "RH"; break;
            case 1:
                type = "BA"; break;
            case 2:
                type = "BD"; break;
            case 3:
                type = "PH"; break;
            case 4:
                type = "WA"; break;
            case 5:
                type = "WD"; break;
            default:
                cerr<<"ERROR: [Board::generatePotions()]: Unknown Random selection."<<endl;
        }
        // create potion, add symbol to map, and invalidate its position
        potions[i] = new Potion(type, position);
        modifyLocation(potions[i]->getPosition()[0], potions[i]->getPosition()[1], 'P');
        Chamber *ch = chambers[chamber];
        ch->setValid(position[0] - ch->getTopCol(), position[1] - ch->getTopRow(), false);
    }
}

/*
 * Purpose: generate the 10 hoards of gold on the board
 * Returns: Nothing
 */
void Board::generateGold() {
    for(int i = 0; i < 10; i++) {
        /* randomize chamber and hoard amount
         *      Normal:     5/8
         *      Dragon:     1/8
         *      Small:      1/4
         */
        int chamber = rand() % 5;
        int random = rand() % 8;
        Chamber *ch = chambers[chamber];
        vector<int> position = ch->generatePosition();
        if(random <= 4) // normal hoard
            goldPiles[i] = new Gold(position, 2, true);
        else if(random <= 6) // small hoard
            goldPiles[i] = new Gold(position, 1, true);
        else if(random == 7) { // dragon hoard
            goldPiles[i] = new Gold(position, 6, false);
            vector<int> dragonPosition = generateNearbyPos(position, chamber, false);
            dragons.push_back(new Dragon(true, chamber, dragonPosition, goldPiles[i], this));
            modifyLocation(dragonPosition[0], dragonPosition[1], 'D');
            ch->setValid(dragonPosition[0] - ch->getTopCol(),
                    dragonPosition[1] - ch->getTopRow(), false);
        }
        // add gold symbol to map, and invalidate its position
        modifyLocation(position[0], position[1], 'G');
        ch->setValid(position[0] - ch->getTopCol(), position[1] - ch->getTopRow(), false);
    }
}

void Board::makeMerchantsHostile() {
    for(int i = 0; i < 20; i++) {
        if(enemies[i]->getRace() == "Merchant") {
            enemies[i]->setHostile();
        }
    }
}
