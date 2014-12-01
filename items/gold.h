#ifndef __GOLD_H__
#define __GOLD_H__
#include "treasure.h"
#include <vector>

class Gold : public Treasure {
    bool available;
 public:
	Gold(std::vector<int> pos, int quantity, bool avail);
	~Gold();
    bool isAvailable();
    void setAvailable(bool avail);
    int getQuantity();
};
#endif
