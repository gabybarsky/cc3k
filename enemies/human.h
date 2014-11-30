#ifndef __HUMAN_H__
#define __HUMAN_H__
#include "enemy.h"

class Human : public Enemy {
 public:
	Human(bool hostile, int chamber, std::vector<int> pos, Board *board);
	~Human();
};
#endif
