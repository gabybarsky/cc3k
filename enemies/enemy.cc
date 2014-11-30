#include "enemy.h"
using namespace std;

/*
 * Enemy constructor, called by all subclasses, calls Character's constructor
 */
Enemy::Enemy(int hp, int atk, int def, char symbol, bool hostile, 
			 int chamber, std::vector<int> pos, std::string race) 
				: Character(hp, atk, def, symbol, pos, race), hostile(hostile), 
							chamber(chamber) {		
}

/*
 * Enemy destructor
 */
Enemy::~Enemy() {
}

/* 
 * Purpose: Return the chamber where this enemy is located
 * Returns: chamber
 */
int Enemy::getChamber() {
    return chamber;
}

/*
 * Purpose: move enemy to newPos
 * Returns: nothing
 */
void Enemy::move(vector<int> newPos) {
    position = newPos;
}
/*
 * Purpose: Makes an enemy hostile
 * Returns: Nothing
 */
void Enemy::setHostile() {
	hostile = true;
}

int Enemy::attack(Player *p) {
    int damage = ceil((100.0 / (100 + p->getDef()) * atk));
	int random = rand() % 2;
	stringstream actionStream;
	if(random == 0) {
		if(damage >= p->getHp()) {
			p->addHp(p->getHp() * -1);
			actionStream<<"PC has been slain";
			p->setAction(actionStream.str());
			return 1;
		}   
		p->addHp(damage * -1);
		actionStream<<"Enemy "<<race<<" dealt "<<damage<<" damage to PC";
	}   
	else
		actionStream<<"Enemy "<<getRace()<<" missed";
	p->setAction(actionStream.str());
	return 0; 
}   
