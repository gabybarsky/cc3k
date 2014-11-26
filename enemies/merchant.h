#ifndef __MERCHANT_H__
#define __MERCHANT_H__
#include "enemy.h"

class Merchant : public Enemy {
 public:
	Merchant();
	void setHostile();
	~Merchant();
};
#endif
