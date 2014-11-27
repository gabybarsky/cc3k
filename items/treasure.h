#ifndef __TREASURE_H__
#define __TREASURE_H__
#include "item.h"

class Treasure : public Item {
 protected:
	int quantity;
	virtual Treasure() = 0;
	virtual ~Treasure() = 0;
};
#endif
