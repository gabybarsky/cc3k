#include "character.h"
#include <vector>
#include <iostream>
using namespace std;

/*
 * 5 parameter constructor for character
 */
Character::Character(int hp, int atk, int def, char sym, vector<int>&pos) 
						: atk(atk), def(def), hp(hp), maxHp(hp), symbol(sym), position(pos) {
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
}
