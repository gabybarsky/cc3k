#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "../character.h"
#include "../items/treasure.h"

class Enemy : public Character {
 protected:
	Treasure *drop;
	bool hostile;
 public:
	virtual Enemy() = 0;
	void attack(Player *p);
	virtual ~Enemy() = 0;
};
#endif
