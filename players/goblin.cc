#include "goblin.h"
#include <vector>
using namespace std;

Goblin::Goblin(int chamber, vector<int> pos)
         : Player(110, 15, 20, chamber, pos, "Goblin") {
}

Goblin::~Goblin() {
}
