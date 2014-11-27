#ifndef __GOLD_H__
#define __GOLD_H__
#include "treasure.h"

class Gold : public Treasure {
 public:
	Gold();
	int getValue();
	~Gold();
};
#endif
