#ifndef __DWARF_H__
#define __DWARF_H__
#include "enemy.h"

class Dwarf : public Enemy {
 public:
	Dwarf(bool hostile, int chamber, std::vector<int> pos);
	~Dwarf();
};
#endif
