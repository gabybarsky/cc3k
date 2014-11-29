#include "dragon.h"
#include <vector>
using namespace std;

/*
 * Dragon constructor, takes in the hoard that the dragon is guarding
 */
Dragon::Dragon(bool hostile, int chamber, vector<int> pos, Gold *hoard) 
				: Enemy(150, 20, 20, 'D', hostile, chamber, pos, "Dragon"), hoard(hoard) {
}

/*
 * Dragon destructor
 */
Dragon::~Dragon() {
}
