#include "character.h"
#include <vector>
#include <iostream>
using namespace std;

/*
 * 5 parameter constructor for character
 */
Character::Character(int hp, int atk, int def, char sym, vector<int>&pos) 
						: atk(atk), def(def), hp(hp), maxHp(hp), symbol(sym), position(pos) {
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
