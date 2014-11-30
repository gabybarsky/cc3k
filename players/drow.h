#ifndef __DROW_H__
#define __DROW_H__
#include "player.h"
#include <vector>

class Drow : public Player {
 public:
	Drow(int chamber, std::vector<int> pos, Board *board);
	~Drow();
};
#endif
