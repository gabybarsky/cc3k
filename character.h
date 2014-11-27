#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <string>
#include <vector>
#include "items/gold.h"

class Character {
 protected:
	int atk;
	int def;
	int hp;
	char symbol;
	std::string special;
    std::vector<int> position;
	
 public:
	Character(int hp, int atk, int def, char sym, std::vector<int>pos);
	//virtual void onTurn() = 0;
	int getAtk();
	int getDef();
	int getHp();
	char getSymbol();
	std::string getSpecial();
	int getRow();
	int getCol();
	//virtual void attack() = 0;
	~Character();
};

#endif
