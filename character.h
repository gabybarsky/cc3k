#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <string>
#include <vector>
#include "gold.h"

class Character {
 protected:
	int atk;
	int def;
	int hp;
	char symbol;
	string special;
	vector<int> position;

 public:
	Character();
	virtual void onTurn() = 0;
	~Character();
};

#endif
