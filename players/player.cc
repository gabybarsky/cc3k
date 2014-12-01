#include "player.h"
#include "../board.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

/*
 * Player constructor, initializes the floor, previous tile, and action
 */
Player::Player(int hp, double atk, double def, int chamber, vector<int>&pos, string race, Board *board)
                : Character(hp, atk, def, '@', pos, race, board),
                  gold(0), chamber(chamber) {
    floor = 0;
    prevTile = '.';
    action = "Player character has spawned.";
    defaultAtk = atk;
    defaultDef = def;
}

/*
 * Player destructor
 */
Player::~Player(){
}

/*
 * Purpose: Getter method for floor
 * Returns: floor
 */
int Player::getFloor() {
    return floor;
}

/*
 * Purpose: Allows the player to move to the next floor
 * Returns: Nothing
 */
void Player::upFloor(int chamber) {
    floor++;
    this->chamber = chamber;
    this->position = board->generatePosition(chamber);
    resetStats();
}

/*
 * Purpose: Getter method for chamber
 * Returns: chamber
 */
int Player::getChamber() {
    return chamber;
}

/*
 * Purpose: Setter method for chamber, allows the player to
 * move between chambers
 * Returns: Nothing
 */
void Player::setChamber(int chamber) {
    this->chamber = chamber;
}

/*
 * Purpose: Getter method for action
 * Returns: action
 */
string Player::getAction() {
    return action;
}

/*
 * Purpose: Adds new text to the action string
 * Returns: Nothing
 */
void Player::addAction(string action) {
    this->action = this->action + action;
}

/*
 * Purpose: Sets text to the action string
 * Returns: Nothing
 */
void Player::setAction(string action) {
    this->action = action;
}

/*
 * Purpose: Setter method for prevTile
 * Returns: Nothing
 */
void Player::setPrevTile(char tile) {
    prevTile = tile;
}

/*
 * Purpose: Adds gold to the player's stash
 * Returns: Nothing
 */
void Player::addGold(int quantity) {
    gold += quantity;
}

/*
 * Purpose: Getter method for gold
 * Returns: gold
 */
int Player::getGold() {
    return gold;
}

/*
 * Purpose: gold string
 * Returns: string of # of gold
 */
string Player::getGoldStr() {
    stringstream ss;
    ss << gold;
    string goldStr;
    ss >> goldStr;
    return goldStr;
}

/*
 * Purpose: add amt atk to player. Does not go below 0
 * Returns: Nothing
 */
void Player::addAtk(double amt) {
	if(atk + amt >= 0)
		atk += amt;
}

/*
 * Purpose: add amt def to player. Does not go below 0
 * Returns: Nothing
 */
void Player::addDef(double amt) {
	if(def + amt >= 0)
		def += amt;
}

/*
 * Purpose: reset stats to base stats
 * Returns: Nothing
 */
void Player::resetStats() {
    atk = defaultAtk;
    def = defaultDef;
}

/*
 * Purpose: learn a new potion
 * Returns: Nothing
 */
void Player::learnPotion(string name) {
    potionKnowledge[name] = true;
}

/*
 * Purpose: does player have knowldege of this potion
 * Returns: true if yes, false otherwise
 */
bool Player::hasKnowledge(string name) {
    if(potionKnowledge.count(name)) {
        return true;
    }
    return false;
}

/*
 * Purpose: Moves the player in the specified direction
 * Returns: Nothing
 */
bool Player::changePosition(string direction) {
    if(direction == "no") {
        position[1] -= 1;
        action = "PC moves North. ";
    } else if (direction == "so") {
        position[1] += 1;
        action = "PC moves South. ";
    } else if (direction == "ea") {
        position[0] += 1;
        action = "PC moves East. ";
    } else if (direction == "we") {
        position[0] -= 1;
        action = "PC moves West. ";
    } else if (direction == "ne") {
        position[1] -= 1;
        position[0] += 1;
        action = "PC moves NorthEast. ";
    } else if (direction == "nw") {
        position[1] -= 1;
        position[0] -= 1;
        action = "PC moves NorthWest. ";
    } else if (direction == "se") {
        position[1] += 1;
        position[0] += 1;
        action = "PC moves SouthEast. ";
    } else if (direction == "sw") {
        position[1] += 1;
        position[0] -= 1;
        action = "PC moves SouthWest. ";
    } else {
        cerr<<"Invalid direction. "<<endl;
        return false;
    }
    return true;
}

/*
 * Purpose: move the player
 * Returns: nothing
 */
void Player::move(string direction) {
    vector<int> prevPos = position; // store previous position for reference
    changePosition(direction);
    char moveTile = board->getLocation(position[0], position[1]);

    /*  
     * For each movement, check validity of the move.
     * If its a bad move, return the player to his previous position and
     * print out the associated action. If its a good move, move the player
     * and validate the old tile as well as invalidate the new player tile
     */
    // if collision with a wall
    if (moveTile == '|' || moveTile == '-') {
        setPosition(prevPos);
        addAction("He hits his head on a wall! ");

    // if stepping on doorway between chambers and tunnels
    } else if (moveTile == '+') {
        board->commitMove(moveTile, prevPos, position, this);
        if(chamber != -1) {
            board->validateTile(true, prevPos, chamber);
        }
        chamber = -1;
    
    // if walking in a tunnel
    } else if (moveTile == '#') {
        board->commitMove(moveTile, prevPos, position, this);
    
    // if interact with stairs
    } else if (moveTile == '\\') {
        prevTile = '.';
        board->moveFloor();

    // if blank spot in chamber
    } else if (moveTile == '.') {
        // check if just entering chamber, if true set players new chamber
        if(prevTile == '+') {
            board->modifyChamber(position);
        }
        // move player and (in)validate new and old player tiles where necessary
        if(board->isValidTile(chamber, position[0], position[1])) {
            if(prevTile != '+') {
                board->validateTile(true, prevPos, chamber);
            }
            board->validateTile(false, position, chamber);
            board->commitMove(moveTile, prevPos, position, this);
        } else {
            // error case. Should NEVER reach this spot. Ghost invalidation occured
            setPosition(prevPos);
            addAction("OH NO WHATS GOING ON THERES A GHOST! ");
        }

    // if attempt to walk into an enemy
    } else if(moveTile == 'H' || moveTile == 'W' || moveTile == 'E' ||
            moveTile == 'O' || moveTile == 'M' || moveTile == 'D' || moveTile == 'L') {
        setPosition(prevPos);
        addAction("He walks straight into an Enemy! OH NOES! ");

    // if attempt to walk into a potion
    } else if(moveTile == 'P') {
        string name = board->getPotionName(position);
        setPosition(prevPos);
        addAction("He sees an unknown Potion! ");
        if(hasKnowledge(name)) {
            addAction(" and see a " + name + " Potion! ");
        } else {
            addAction(" and sees an unknown Potion! ");
        }

    // if walking over Gold pick it up
    } else if(moveTile == 'G') {
        if(board->pickupGold(position)) {
            board->commitMove('.', prevPos, position, this);
            board->validateTile(true, prevPos, chamber);
        } else {
            setPosition(prevPos);
        }
    }
} 

/*
 * Purpose: Allows the player to attack an enemy
 * Returns: Nothing
 */
int Player::attack(Character *e) {
	int damage = ceil((100.0 / (100 + e->getDef())) * atk);
	stringstream actionStream;
    e->addHp(damage * -1);
	if(e->getHp() <= 0) {
		actionStream<<"Enemy "<<e->getRace()<<" has been slain. ";
		action = actionStream.str();
		return 1;
	}
	actionStream<<"PC dealt "<<damage<<" damage to Enemy "<<e->getRace()<<". ";
	action += actionStream.str();
	actionStream.str("");
	return 0;
}

bool Player::isNearby(Character *e) {
	vector<int> playerPos = getPosition();
	vector<int> enemyPos = e->getPosition();
	if((playerPos[0]-enemyPos[0] <= 1)&&(playerPos[0]-enemyPos[0] >= -1)
		&&(playerPos[1]-enemyPos[1] <= 1)&&(playerPos[1]-enemyPos[1]>= -1))
		return true;
	else
		return false;
}
