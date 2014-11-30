#include "human.h"
#include <vector>
using namespace std;

/*
 * Human constructor
 */
Human::Human(bool hostile, int chamber, vector<int> pos, Board *board)
				: Enemy(140, 20, 20, 'H', hostile, chamber, pos, "Human", board) {
}

/*
 * Human destructor
 */
Human::~Human() {
}
