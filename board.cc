#include "board.h"
#include "chamber.h"
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
    char character = playerSelect();
    int temp = rand() % 5;
    chambers[temp]->generatePlayer(character);

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
        //chambers[ch]->generateChamber();
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
 * Purpose: move up a floor, clean last floor and create a new one
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

/*
 * Purpose: insert a player character into the map
 * Returns: Nothing
 */
void Board::insertPlayer() {
    vector<int> pos = player->getPosition();
    modifyLocation(pos[0], pos[1], player->getSymbol());
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
    player->move(direction); //move the player in the desired direction
    vector<int> newPos = player->getPosition(); // store new position for reference
    char moveTile = getLocation(newPos[0], newPos[1]); // get the tile player moves to

    /*
     * For each movement, check validity of the move.
     * If its a bad move, return the player to his previous position and
     * print out the associated action. If its a good move, move the player
     * and validate the old tile as well as invalidate the new player tile
     */
    // if potion command and no potion in the direction
    if(usePotion && moveTile != 'P') {
        player->setPosition(prevPos);
        player->setAction("PC tries to use Potion but there is no Potion around!");

    // if attack command but no enemy in the direction
    } else if(attack && moveTile != 'H' && moveTile != 'W' && moveTile != 'E' &&
           moveTile != 'O' && moveTile != 'M' && moveTile != 'D' && moveTile != 'L') {
        player->setPosition(prevPos);
        player->setAction("PC tries to attack but there is no Enemy around!");

    // if collision with a wall
    } else if(moveTile == '|' || moveTile == '-') {
        player->setPosition(prevPos);
        player->addAction(" and hits his head on a wall!");

    // if stepping onto a doorway between chambers and tunnels
    } else if (moveTile == '+') {
        commitMove(moveTile, prevPos, newPos);
        if (player->getChamber() != -1) {
            validateTile(true, prevPos, player->getChamber());
        }
        player->setChamber(-1);

    // if walking in a tunnel
    } else if (moveTile == '#') {
        commitMove(moveTile, prevPos, newPos);

    // if interact with stairs
    } else if (moveTile == '\\') {
        player->setPrevTile('.');
        moveFloor();

    // if try to move onto a void spot
    } else if (moveTile == ' ') {
        player->setPosition(prevPos);
        player->addAction(" and almost falls into the void.");

    // if blank spot
    } else if(moveTile == '.') {
        // check if just entering the chamber. if true, set players new chamber
        if (player->getPrevTile() == '+') {
            modifyChamber(newPos);
        }
        // move player and (in)validate new and old player tiles where necessary
        Chamber *ch = chambers[player->getChamber()]; 
        if(ch->isValidTile(newPos[0] - ch->getTopCol(), newPos[1] - ch->getTopRow())) {
            if(player->getPrevTile() != '+') {
                validateTile(true, prevPos, player->getChamber());
            }
            validateTile(false, newPos, player->getChamber());
            commitMove(moveTile, prevPos, newPos);
        } else {
            // error case. Should NEVER reach this spot. Ghost invalidation has occured
            player->setPosition(prevPos);
            player->addAction(" OH NO WHATS GOING ON THERES A GHOST!");
        }

    // if attempt to walk into an enemy
    } else if(moveTile == 'H' || moveTile == 'W' || moveTile == 'E' ||
            moveTile == 'O' || moveTile == 'M' || moveTile == 'D' || moveTile == 'L') {
        player->setPosition(prevPos);
        player->addAction(" and walks straight into an Enemy! OH NOES!");

    // if attempt to walk into a potion
    } else if(moveTile == 'P') {
        player->setPosition(prevPos);
        // command to usePotion 'u' was declared
        if (usePotion) {
            for(int i = 0; i < 10; i++) {
                if(potions[i]->getPosition() == newPos) {
                    // found potion in array. No need to delete the memory allocation.
                    // Refer to gold pickup for more info
                    player->setAction("PC uses " + potions[i]->getName());
                    potions[i]->use(*player);
                    modifyLocation(newPos[0], newPos[1], '.');
                    validateTile(true, newPos, player->getChamber());
                }
            }
        } else {
            player->addAction(" and sees an unknown Potion!");
        }

    // if walking over a piece of gold, pick it up
    } else if(moveTile == 'G') {
        for(int i = 0; i < 10; i++) {
            if(goldPiles[i]->getPosition() == newPos) {
                // found gold piece in array. No need to delete the memory allocation
                // since tile will no longer display 'G' and therefore no duplicate
                // gold will be grabbed. Deletion can be done in cleanup
                int quantity = goldPiles[i]->getQuantity();
                player->addGold(quantity);
                commitMove('.', prevPos, newPos);
				stringstream actionStream;
				actionStream<<" and finds "<<quantity<<((quantity == 1) ? " piece" : " pieces")<<" of gold!";
                string action = actionStream.str();
                player->addAction(action);
                validateTile(true, prevPos, player->getChamber());             
                break;
            }
        }
    }
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
void Board::commitMove(char moveTile, vector<int> prevPos, vector<int> newPos) {
    modifyLocation(prevPos[0], prevPos[1], player->getPrevTile());
    player->setPrevTile(moveTile);
    modifyLocation(newPos[0], newPos[1], player->getSymbol());
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
 * Purpose: generate the position of a Dragon Enemy relative to
 *          the pos of a dragon gold hoard.
 * Returns: vector<int> position of the dragon
 */
vector<int> Board::generateDragonPos(vector<int> pos) {
    // random x and y each between -1 and 1
	int x = rand() % 2 - 1;
	int y = rand() % 2 - 1;
    // make sure x and y are not BOTH 0
	while(x == 0 && y == 0) {
		x = rand() % 2 - 1;
		y = rand() % 2 - 1;
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
            e = new Human(true, random, position); break;
        case 'W':
            e = new Dwarf(true, random, position); break;
        case 'L':
            e = new Halfling(true, random, position); break;
        case 'E':
            e = new Elf(true, random, position); break;
        case 'M':
            e = new Merchant(false, random, position); break;
        case 'O':
            e = new Orc(true, random, position); break;
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
		vector<int> position = chambers[chamber]->generatePosition();
		if(random <= 4) // normal hoard
			goldPiles[i] = new Gold(position, 2);
		else if(random <= 6) // small hoard
			goldPiles[i] = new Gold(position, 1);
		else if(random == 7) { // dragon hoard
			goldPiles[i] = new Gold(position, 6);
			vector<int> dragonPosition = generateDragonPos(position);
			dragons.push_back(new Dragon(true, chamber, dragonPosition, goldPiles[i]));
			modifyLocation(dragonPosition[0], dragonPosition[1], 'D');
		}
        // add gold symbol to map, and invalidate its position
		modifyLocation(position[0], position[1], 'G');
        Chamber *ch = chambers[chamber];
        ch->setValid(position[0] - ch->getTopCol(), position[1] - ch->getTopRow(), false);
	}
}
