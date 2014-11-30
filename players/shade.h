#ifndef __SHADE_H__
#define __SHADE_H__
#include "player.h"
#include <vector>

class Shade : public Player {
 public:
	Shade(int chamber, std::vector<int>pos, Board *board);
	~Shade();
};
#endif
