#include "enemy.h"
using namespace std;

Enemy::Enemy(int hp, int atk, int def, char symbol, bool hostile, 
			 int chamber, std::vector<int> pos, std::string race) 
				: Character(hp, atk, def, symbol, pos), hostile(hostile), 
							chamber(chamber), race(race) {		
}

Enemy::~Enemy() {
}

int Enemy::getChamber() {
    return chamber;
}
