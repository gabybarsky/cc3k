#ifndef __DRAGON_H__
#define __DRAGON_H__
#include "enemy.h"

class Dragon : public Enemy {
	Gold* hoard;
 public:
	Dragon(bool hostile, int chamber, std::vector<int> pos, Gold* hoard);
	~Dragon();
};
#endif
