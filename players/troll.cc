#include "troll.h"
#include <vector>
using namespace std;

/*
 * Troll constructor
 */
Troll::Troll(int chamber, vector<int> pos, Board *board)
         : Player(120, 25, 15, chamber, pos, "Troll", board) {
}

/*
 * Troll destructor
 */
Troll::~Troll() {
}
