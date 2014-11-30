#include "orc.h"
#include <vector>
using namespace std;

/*
 * Orc constructor
 */
Orc::Orc(bool hostile, int chamber, vector<int> pos, Board *board)
			: Enemy(180, 30, 25, 'O', hostile, chamber, pos, "Orc", board) {
}

/*
 * Orc destructor
 */
Orc::~Orc() {
}
