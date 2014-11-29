#ifndef __POTION_H__
#define __POTION_H__
#include "item.h"
#include "../character.h"
#include "../potionDecorator.h"
#include <string>
#include <vector>

class Potion : public Item {
	int value;
	std::string stat;
 public:
	Potion(std::string type, std::vector<int> pos);
	void use(Character &c);
	~Potion();
};
#endif
