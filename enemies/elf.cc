#include "elf.h"
#include <vector>
using namespace std;

/*
 * Elf constructor
 */
Elf::Elf(bool hostile, int chamber, vector<int> pos, Board *board)
			: Enemy(140, 30, 10, 'E', hostile, chamber, pos, "Elf", board){
}

/*
 * Elf destructor
 */
Elf::~Elf() {
}
