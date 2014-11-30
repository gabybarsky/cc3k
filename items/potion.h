#ifndef __POTION_H__
#define __POTION_H__
#include "item.h"
#include "../players/player.h"
#include <string>
#include <vector>

class Potion : public Item {
	int value;
	std::string stat;
 public:
	Potion(std::string type, std::vector<int> pos);
	void use(Player &p);
	~Potion();
};
#endif
