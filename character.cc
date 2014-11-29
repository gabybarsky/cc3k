#include "character.h"
#include <vector>
#include <iostream>
using namespace std;

/*
 * Default constructor for character
 */
Character::Character() : atk(0), def(0), hp(0), symbol(0), position() {
}

/*
 * 5 parameter constructor for character
 */
Character::Character(int hp, int atk, int def, char sym, vector<int>&pos) : atk(atk), def(def), hp(hp), symbol(sym), position(pos) {
}

/*
 * Copy constructor for character
 */
Character::Character(Character &c) {
	hp = c.hp;
	atk = c.getAtk();
	def = c.getDef();
	symbol = c.getSymbol();
	position = c.getPosition();
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
