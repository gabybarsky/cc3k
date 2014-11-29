#include "potionDecorator.h"
using namespace std;

/*
 * Constructor for PotionDecorator
 */
PotionDecorator::PotionDecorator(Character &c, string stat, int value)
									: Decorator(c), stat(stat), value(value) {
}

/*
 * Purpose: Getter method for atk to apply the stat modification
 */
int PotionDecorator::getAtk() {
	if(stat=="atk")
		return c.getAtk() + value;
	else
		return c.getAtk();
}

/*
 * Purpose: Getter method for def to apply the stat modification
 */
int PotionDecorator::getDef() {
	if(stat=="def")
		return c.getDef() + value;
	else
		return c.getDef();
}

/*
 * Purpose: Getter method for hp to apply the stat modification
 */
int PotionDecorator::getHp() {
	if(stat=="hp")
		return c.getHp() + value;
	else
		return c.getDef();
}

/*
 * Destructor for PotionDecorator
 */
PotionDecorator::~PotionDecorator() {
}
