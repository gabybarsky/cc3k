#ifndef __POTION_H__
#define __POTION_H__
#include "item.h"
#include "../character.h"
#include "../potionDecorator.h"

class Potion : public Item {
	int value;
	std::string stat;
 public:
	Potion(std::string type);
	void use(Character &c);
	~Potion();
};
#endif
