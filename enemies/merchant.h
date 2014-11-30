#ifndef __MERCHANT_H__
#define __MERCHANT_H__
#include "enemy.h"

class Merchant : public Enemy {
 public:
	Merchant(bool hostile, int chamber, std::vector<int> pos, Board *board);
	~Merchant();
};
#endif
