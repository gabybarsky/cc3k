#include "merchant.h"
#include <vector>
using namespace std;

/*
 * Merchant constructor
 */
Merchant::Merchant(bool hostile, int chamber, vector<int> pos)
					: Enemy(30, 70, 5, 'M', hostile, chamber, pos, "Merchant") { 
}

/*
 * Merchant destructor
 */
Merchant::~Merchant() {
}
