#include "potionDecorator.h"
using namespace std;

PotionDecorator::PotionDecorator(Character &c, string stat, int value)
									: Decorator(c), stat(stat), value(value) {
}

int PotionDecorator::getAtk() {
	if(stat=="atk")
		return c.getAtk() + value;
	else
		return c.getAtk();
}

int PotionDecorator::getDef() {
	if(stat=="def")
		return c.getDef() + value;
	else
		return c.getDef();
}

int PotionDecorator::getHp() {
	if(stat=="hp")
		return c.getHp() + value;
	else
		return c.getDef();
}

PotionDecorator::~PotionDecorator() {
}
