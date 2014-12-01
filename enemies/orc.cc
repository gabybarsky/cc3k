#include "orc.h"
#include <vector>
using namespace std;

/*
 * Orc constructor
 */
Orc::Orc(bool hostile, int chamber, vector<int> pos, Board *board)
			: Enemy(180, 30, 25, 'O', hostile, chamber, pos, "Orc", board) {
}

int Orc::attack(Player *p) {
	if(p->getRace() != "Goblin")
		return Enemy::attack(p);
	int damage = ceil((100.0 / (100 + p->getDef()) * atk) * 1.5);
	int random = rand() % 2;
	stringstream actionStream;
	if(random == 0) {
		if(damage >= p->getHp()) {
			p->addHp(p->getHp() * -1);
			actionStream<<"PC has been slain. ";
			p->setAction(actionStream.str());
			return 1;
		}
		p->addHp(damage * -1);
		actionStream<<"Enemy Orc ("<<hp<<"HP) dealt "<<damage<<" to PC. ";
	} else {
		actionStream<<"Enemy Orc ("<<hp<<"HP) missed. ";
	}
	p->addAction(actionStream.str());
	return 0;
}

/*
 * Orc destructor
 */
Orc::~Orc() {
}
