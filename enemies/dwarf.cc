#include "dwarf.h"
#include <vector>
using namespace std;

/*
 * Dwarf Constructor
 */
Dwarf::Dwarf(bool hostile, int chamber, vector<int> pos, Board *board) 
         : Enemy(100, 20, 30, 'W', hostile, chamber, pos, "Dwarf", board) {
}

/*
 * Dwarf Destructor
 */
Dwarf::~Dwarf() {
}
