#ifndef __POTION_H__
#define __POTION_H__
#include "item.h"

class Potion : public Item {
	int value;
	int turns;
	string stat;
 public:
	Potion();
	void use(Character &c);
	~Potion();
};
#endif
