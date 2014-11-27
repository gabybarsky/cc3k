#include "troll.h"
#include <vector>
using namespace std;

Troll::Troll(int chamber, vector<int> pos)
         : Player(hp, atk, def, chamber, pos, "Troll") {
}

Troll::~Troll() {
}
