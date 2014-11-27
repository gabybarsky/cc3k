#ifndef __TREASURE_H__
#define __TREASURE_H__
#include "item.h"
#include <string>

class Treasure : public Item {
 protected:
	int quantity;
	Treasure(std::string name);
	virtual ~Treasure() = 0;
};
#endif
