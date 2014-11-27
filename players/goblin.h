#ifndef __GOBLIN_H__
#define __GOBLIN_H__
#include "player.h"
#include <vector>

class Goblin : public Player {
 public:
	Goblin(int chamber, std::vector<int> pos);
	~Goblin();
};
#endif
