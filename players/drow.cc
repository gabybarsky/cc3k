#include "drow.h"
#include <vector>
using namespace std;

Drow::Drow(int chamber, vector<int> pos)
         : Player(hp, atk, def, chamber, pos, "Drow") {
}

Drow::~Drow() {
}
