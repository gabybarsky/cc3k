#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "../character.h"

class Enemy : public Character {
 protected:
	int drop;
	bool hostile;
 public:
	virtual Enemy() = 0;
	virtual ~Enemy() = 0;
};
#endif
