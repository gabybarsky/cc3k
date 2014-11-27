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
	std::string special;
	vector<int> position;
	
 public:
	Character();
	virtual void onTurn() = 0;
	int getAtk();
	int getDef();
	int getHp();
	char getSymbol();
	std::string getSpecial();
	int getRow();
	int getCol();
	void move(std::string direction);
	virtual void attack() = 0;
	~Character();
};

#endif
