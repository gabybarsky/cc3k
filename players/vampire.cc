#include "vampire.h"
#include <vector>
using namespace std;

/*
 * Vampire constructor
 */
Vampire::Vampire(int chamber, vector<int> pos, Board *board)
         : Player(50, 25, 25, chamber, pos, "Vampire", board) {
}

/*
 * Purpose: overloaded attack method to allow vampire to restore 5 HP on attack
 * Returns: 1 if the enemy was killed, 0 otherwise
 */
int Vampire::attack(Character *e) {
	int result = Player::attack(e);
	hp+=5;
	return result;
}

/*
 * Vampire destructor
 */
Vampire::~Vampire() {
}
