#ifndef __HALFLING_H__
#define __HALFLING_H__
#include "enemy.h"

class Halfling : public Enemy {
 public:
	Halfling(bool hostile, int chamber, std::vector<int> pos, Board *board);
	~Halfling();
};
#endif
