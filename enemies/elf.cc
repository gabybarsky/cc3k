#include "elf.h"
#include <vector>
using namespace std;

Elf::Elf(bool hostile, int chamber, vector<int> pos)
			: Enemy(140, 30, 10, 'E', hostile, chamber, pos, "Elf"){
}

Elf::~Elf() {
}
