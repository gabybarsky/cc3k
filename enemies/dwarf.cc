#include "dwarf.h"
#include <vector>
using namespace std;

Dwarf::Dwarf(bool hostile, int chamber, vector<int> pos) : Enemy(100, 20, 30, 'W', hostile, chamber, pos, "Dwarf") {
}

Dwarf::~Dwarf() {
}
