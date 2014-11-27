#ifndef __TROLL_H__
#define __TROLL_H__
#include "player.h"
#include <vector>

class Troll : public Player {
 public:
	Troll(int chamber, std::vector<int> pos);
	~Troll();
};
#endif
