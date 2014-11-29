#include "orc.h"
#include <vector>
using namespace std;

/*
 * Orc constructor
 */
Orc::Orc(bool hostile, int chamber, vector<int> pos)
			: Enemy(180, 30, 25, 'O', hostile, chamber, pos, "Orc") {
}

/*
 * Orc destructor
 */
Orc::~Orc() {
}
