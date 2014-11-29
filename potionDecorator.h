#ifndef __POTION_DECORATOR_H__
#define __POTION_DECORATOR_H__
#include "decorator.h"
#include <string>

class PotionDecorator : public Decorator {
	std::string stat;
	int value;
 public:
	PotionDecorator(Character &c, std::string stat, int value);
	int getAtk();
	int getDef();
	int getHp();
	~PotionDecorator();
};
#endif
