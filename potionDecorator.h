#ifndef __POTION_DECORATOR_H__
#define __POTION_DECORATOR_H__
#include "decorator.h"

class PotionDecorator : public Decorator {
	int value;
	string stat;
 public:
	PotionDecorator(Character &c);
	~PotionDecorator();
};
#endif
