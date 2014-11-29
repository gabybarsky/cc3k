#include "drow.h"
#include <vector>
using namespace std;

/*
 * Drow constructor
 */
Drow::Drow(int chamber, vector<int> pos)
         : Player(150, 25, 15, chamber, pos, "Drow") {
}

/*
 * Drow destructor
 */
Drow::~Drow() {
}
