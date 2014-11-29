#include "troll.h"
#include <vector>
using namespace std;

/*
 * Troll constructor
 */
Troll::Troll(int chamber, vector<int> pos)
         : Player(120, 25, 15, chamber, pos, "Troll") {
}

/*
 * Troll destructor
 */
Troll::~Troll() {
}
