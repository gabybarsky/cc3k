#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "../character.h"
#include "../items/treasure.h"
#include <string>
#include <vector>

class Enemy : public Character {
 protected:
	Treasure *drop;
	bool hostile;
	int chamber;
	std::string race;
 public:
	Enemy(int hp, int atk, int def, char symbol, bool hostile, int chamber, std::vector<int> pos, std::string race);
	virtual ~Enemy();
    int getChamber();
};
#endif
