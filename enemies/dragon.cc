#include "dragon.h"
#include <vector>
using namespace std;

Dragon::Dragon(bool hostile, int chamber, vector<int> pos, Gold *hoard) 
				: Enemy(150, 20, 20, 'D', hostile, chamber, pos, "Dragon") {
}

Dragon::~Dragon() {
}
