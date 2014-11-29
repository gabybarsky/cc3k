#include "shade.h"
#include <vector>
using namespace std;

/*
 * Shade constructor
 */
Shade::Shade(int chamber, vector<int> pos)
        : Player(125, 25, 25, chamber, pos, "Shade") {
}

/*
 * Shade destructor
 */
Shade::~Shade() {
}
