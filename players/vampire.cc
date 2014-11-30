#include "vampire.h"
#include <vector>
using namespace std;

/*
 * Vampire constructor
 */
Vampire::Vampire(int chamber, vector<int> pos, Board *board)
         : Player(50, 25, 25, chamber, pos, "Vampire", board) {
}

/*
 * Vampire destructor
 */
Vampire::~Vampire() {
}
