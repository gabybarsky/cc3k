#include "vampire.h"
#include <vector>
using namespace std;

Vampire::Vampire(int chamber, vector<int> pos)
         : Player(hp, atk, def, chamber, pos, "Vampire") {
}

Vampire::~Vampire() {
}
