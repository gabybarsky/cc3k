#include "drow.h"
#include <vector>
using namespace std;

/*
 * Drow constructor
 */
Drow::Drow(int chamber, vector<int> pos, Board *board)
         : Player(150, 25, 15, chamber, pos, "Drow", board) {
}

/*
 * Drow destructor
 */
Drow::~Drow() {
}
