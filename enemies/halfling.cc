#include "halfling.h"
#include <vector>
using namespace std;

/*
 * Halfling constructor
 */
Halfling::Halfling(bool hostile, int chamber, vector<int> pos, Board *board)
					: Enemy(100, 15, 20, 'L', hostile, chamber, pos, "Halfling", board) {
}

/*
 * Halfling destructor
 */
Halfling::~Halfling() {
}
