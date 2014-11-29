#ifndef __TREASURE_H__
#define __TREASURE_H__
#include "item.h"
#include <string>
#include <vector>

class Treasure : public Item {
 protected:
	int quantity;
	Treasure(std::string name, std::vector<int> pos, int quantity);
	~Treasure();
};
#endif
