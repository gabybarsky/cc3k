#include "elf.h"
#include <vector>
using namespace std;

/*
 * Elf constructor
 */
Elf::Elf(bool hostile, int chamber, vector<int> pos, Board *board)
			: Enemy(140, 30, 10, 'E', hostile, chamber, pos, "Elf", board){
}

int Elf::attack(Player *p) {
	int result = Enemy::attack(p);
	if(p->getRace() != "Drow" && result != 1)
		result = Enemy::attack(p);
	return result;
}

/*
 * Elf destructor
 */
Elf::~Elf() {
}
