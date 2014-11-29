#include "halfling.h"
#include <vector>
using namespace std;

/*
 * Halfling constructor
 */
Halfling::Halfling(bool hostile, int chamber, vector<int> pos)
					: Enemy(100, 15, 20, 'L', hostile, chamber, pos, "Halfling") {
}

/*
 * Halfling destructor
 */
Halfling::~Halfling() {
}
