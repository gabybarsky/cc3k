#include "character.h"
using namespace std;

Character::Character(int hp, int atk, int def, char sym, vector<int>pos) : atk(atk), def(def), hp(hp), symbol(sym), position(pos) {
}

Character::~Character() {
}

int Character::getAtk() {
	return atk;
}

int Character::getDef() {
	return def;
}

int Character::getHp() {
	return hp;
}

char Character::getSymbol() {
	return symbol;
}

int Character::getRow() {
	return position[0];
}

int Character::getCol() {
	return position[1];
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
