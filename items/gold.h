#ifndef __GOLD_H__
#define __GOLD_H__
#include "treasure.h"
#include <vector>

class Gold : public Treasure {
 public:
	Gold(std::vector<int> pos, int quantity);
	~Gold();
    int getQuantity();
};
#endif
