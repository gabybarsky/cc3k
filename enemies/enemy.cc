#include "enemy.h"
using namespace std;

/*
 * Enemy constructor, called by all subclasses, calls Character's constructor
 */
Enemy::Enemy(int hp, int atk, int def, char symbol, bool hostile, 
			 int chamber, std::vector<int> pos, std::string race) 
				: Character(hp, atk, def, symbol, pos), hostile(hostile), 
							chamber(chamber), race(race) {		
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
