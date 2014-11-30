#include "character.h"
#include <vector>
#include <iostream>
using namespace std;

/*
 * 6 parameter constructor for character
 */
Character::Character(int hp, int atk, int def, char sym, vector<int> &pos, string race) 
						: atk(atk), def(def), hp(hp), maxHp(hp), symbol(sym), position(pos), race(race) {
	prevTile = '.';
}

/*
 * Destructor for character
 */
Character::~Character() {
}

/*
 * Purpose: Getter method for atk
 * Returns: atk
 */
int Character::getAtk() {
	return atk;
}

/*
 * Purpose: Getter method for def
 * Returns: def
 */
int Character::getDef() {
	return def;
}

/*
 * Purpose: Getter method for hp
 * Returns: hp
 */
int Character::getHp() {
	return hp;
}

/*
 * Purpose: Getter method for symbol
 * Returns: symbol
 */
char Character::getSymbol() {
	return symbol;
}

/*
 * Purpose: Getter method for position
 * Returns: position
 */
vector<int> Character::getPosition() {
    return position;
}

/*
 * Purpose: getter method for prevTile
 * Returns: prevTile
 */
char Character::getPrevTile() {
    return prevTile;
}

/*
 * Purpose: default setter for prevTile
 * Returns: nothing
 */
void Character::setPrevTile(char tile) {
	prevTile = tile;
}
/*
 * Purpose: Getter method for race
 * Returns: race
 */
string Character::getRace() {
	return race;
}

void Character::addHp(int amt) {
	if(hp + amt <= maxHp)
		hp += amt;
	else
		hp = maxHp;
}

/*
void Character::move(string direction) {
	switch(direction) {
		case "no":
			position[0]++;
			break;
		case "so":
			position[0]--;
			break;
		case "ea":
			position[1]++;
			break;
		case "we":
			position[1]--;
			break;
		case "ne":
			position[0]++;
			position[1]++;
			break;
		case "nw":
			position[0]++;
			position[1]--;
			break;
		case "se":
			position[0]--;
			position[1]++;
			break;
		case "sw":
			position[0]--;
			position[1]--;
			break;
		default:
			cerr<<"Invalid direction"<<endl;
	}
}*/
