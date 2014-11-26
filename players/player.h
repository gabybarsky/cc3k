#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "../character.h"

class Player : public Character {
 protected:
	int gold;
 public:
	virtual Player() = 0;
	virtual ~Player() = 0;
};
#endif
