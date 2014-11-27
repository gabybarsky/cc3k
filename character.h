#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <string>
#include <vector>
#include "../items/gold.h"

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
	int getAtk();
	int getDef();
	int getHp();
	char getSymbol();
	string getSpecial();
	vector<int> getPosition();
	void move(char direction);
	~Character();
};

#endif
