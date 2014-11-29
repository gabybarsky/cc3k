#ifndef __DECORATOR_H__
#define __DECORATOR_H__
#include "character.h"

class Decorator : public Character {
 protected:
	Character &c;
	Decorator(Character &c);
	~Decorator();//The decorator takes ownership of the character
};
#endif
