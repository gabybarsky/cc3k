#ifndef __ELF_H__
#define __ELF_H__
#include "enemy.h"

class Elf : public Enemy {
 public:
	Elf(bool hostile, int chamber, std::vector<int> pos, Board *board);
	~Elf();
};
#endif
