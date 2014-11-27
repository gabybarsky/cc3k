#include "goblin.h"
#include <vector>
using namespace std;

Goblin::Goblin(int chamber, vector<int> pos)
         : Player(hp, atk, def, chamber, pos, "Goblin") {
}

Goblin::~Goblin() {
}
