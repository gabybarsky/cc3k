#include "vampire.h"
#include <vector>
using namespace std;

Vampire::Vampire(int chamber, vector<int> pos)
         : Player(50, 25, 25, chamber, pos, "Vampire") {
}

Vampire::~Vampire() {
}
