#ifndef __DRAGON_H__
#define __DRAGON_H__
#include "enemy.h"

class Dragon : public Enemy {
	Gold* hoard;
 public:
	Dragon();
	~Dragon();
};
#endif
