#ifndef __ORC_H__
#define __ORC_H__
#include "enemy.h"

class Orc : public Enemy {
 public:
	Orc(bool hostile, int chamber, std::vector<int> pos, Board *board);
	~Orc();
};
#endif
