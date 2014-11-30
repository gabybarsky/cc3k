#include "goblin.h"
#include <vector>
using namespace std;

/*
 * Goblin constructor
 */
Goblin::Goblin(int chamber, vector<int> pos, Board *board)
         : Player(110, 15, 20, chamber, pos, "Goblin", board) {
}

/*
 * Goblin destructor
 */
Goblin::~Goblin() {
}
