#include "shade.h"
#include <vector>
using namespace std;

/*
 * Shade constructor
 */
Shade::Shade(int chamber, vector<int> pos, Board *board)
        : Player(125, 25, 25, chamber, pos, "Shade", board) {
}

/*
 * Shade destructor
 */
Shade::~Shade() {
}
