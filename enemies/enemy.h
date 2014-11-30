#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "../character.h"
#include "../items/treasure.h"
#include "../players/player.h"
#include <sstream>
#include <string>
#include <vector>

class Player;

class Enemy : public Character {
 protected:
	Treasure *drop;
	bool hostile;
	int chamber;
 public:
	Enemy(int hp, int atk, int def, char symbol, bool hostile, int chamber, std::vector<int> pos, std::string race, Board *board);
	virtual ~Enemy();
    int getChamber();
	void setHostile();
	int attack(Player *p);
    void move(std::string direction = "");
};
#endif
