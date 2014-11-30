#include "player.h"
using namespace std;

/*
 * Player constructor, initializes the floor, previous tile, and action
 */
Player::Player(int hp, int atk, int def, int chamber, vector<int>&pos, string race)
                : Character(hp, atk, def, '@', pos, race),
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
void Player::upFloor() {
    floor++;
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
 * Purpose: Setter method for position
 * Returns: Nothing
 */
void Player::setPosition(vector<int> pos) {
    position = pos;
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
 * Purpose: add amt atk to player. Does not go below 0
 * Returns: Nothing
 */
void Player::addAtk(int amt) {
	if(atk + amt >= 0)
		atk += amt;
}

/*
 * Purpose: add amt def to player. Does not go below 0
 * Returns: Nothing
 */
void Player::addDef(int amt) {
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
 * Purpose: Moves the player in the specified direction
 * Returns: Nothing
 */
void Player::move(string direction) {
    if(direction == "no") {
        position[1] -= 1;
        action = "PC moves North";
    } else if (direction == "so") {
        position[1] += 1;
        action = "PC moves South";
    } else if (direction == "ea") {
        position[0] += 1;
        action = "PC moves East";
    } else if (direction == "we") {
        position[0] -= 1;
        action = "PC moves West";
    } else if (direction == "ne") {
        position[1] -= 1;
        position[0] += 1;
        action = "PC moves NorthEast";
    } else if (direction == "nw") {
        position[1] -= 1;
        position[0] -= 1;
        action = "PC moves NorthWest";
    } else if (direction == "se") {
        position[1] += 1;
        position[0] += 1;
        action = "PC moves SouthEast";
    } else if (direction == "sw") {
        position[1] += 1;
        position[0] -= 1;
        action = "PC moves SouthWest";
    } else {
        cerr<<"Invalid direction"<<endl;
    }
}

/*
 * Purpose: Allows the player to attack an enemy
 * Returns: Nothing
 */
 int Player::attack(Enemy *e) {
	int damage = ceil((100 / (100 + e->getDef())) * atk);
	stringstream actionStream;
	if(damage >= e->getHp()) {
		actionStream<<"Enemy "<<e->getRace()<<" has been slain";
		return 1;
	}
	e->addHp(damage * -1);
	actionStream<<"PC dealt "<<" damage to Enemy "<<e->getRace();
	damage = ceil((100 / (100 + def) * e->getAtk()));
	int random = rand() % 2;
	action = actionStream.str();
	if(random == 1) {
		if(damage >= hp) {
			actionStream<<"PC has been slain";
			return -1;
		}
		addHp(damage * -1);
		actionStream<<"Enemy "<<e->getRace()<<" dealt "<<damage<<" damage to PC";
	}
	else
		actionStream<<"Enemy "<<e->getRace()<<" missed";
	action = actionStream.str();
	return 0;
}
