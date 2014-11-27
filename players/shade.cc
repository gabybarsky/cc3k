#include "shade.h"
#include <vector>
using namespace std;

Shade::Shade(int chamber, vector<int> pos)
        : Player(hp, atk, def, chamber, pos, "Shade") {
}

Shade::~Shade() {
}
