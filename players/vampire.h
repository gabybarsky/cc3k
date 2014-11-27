#ifndef __VAMPIRE_H__
#define __VAMPIRE_H__
#include "player.h"
#include <vector>

class Vampire : public Player {
 public:
	Vampire(int chamber, std::vector<int> pos);
	~Vampire();
};
#endif
