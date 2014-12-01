#include "character.h"
#include <vector>
#include <iostream>
using namespace std;

/*
 * 7 parameter constructor for character
 */
Character::Character(int hp, double atk, double def, char sym, vector<int> &pos, string race, Board *board) 
						: atk(atk), def(def), hp(hp), maxHp(hp), symbol(sym), position(pos), race(race), board(board) {
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
double Character::getAtk() {
	return atk;
}

/*
 * Purpose: Getter method for def
 * Returns: def
 */
double Character::getDef() {
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
 * Purpose: Setter method for position
 * Returns: nothing
 */
void Character::setPosition(vector<int> pos) {
    position = pos;
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

/*
 * Purpose: modify hp of character by amt
 * Returns: nothing
 */
void Character::addHp(int amt) {
	if(hp + amt <= maxHp)
		hp += amt;
	else
		hp = maxHp;
}
