#include "human.h"
#include <vector>
using namespace std;

Human::Human(bool hostile, int chamber, vector<int> pos)
				: Enemy(140, 20, 20, 'H', hostile, chamber, pos, "Human") {
}

Human::~Human() {
}
