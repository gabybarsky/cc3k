#include "vampire.h"
#include <vector>
using namespace std;

/*
 * Vampire constructor
 */
Vampire::Vampire(int chamber, vector<int> pos)
         : Player(50, 25, 25, chamber, pos, "Vampire") {
}

/*
 * Vampire destructor
 */
Vampire::~Vampire() {
}
