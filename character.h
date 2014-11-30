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
	int max;
	char symbol;
	std::string special;
    std::vector<int> position;
	
 public:
	Character();
	Character(int hp, int atk, int def, char sym, std::vector<int> &pos);
	Character(Character &c);
	//virtual void onTurn() = 0;
	int getAtk();
	int getDef();
	int getHp();
	char getSymbol();
	std::string getSpecial();
    std::vector<int> getPosition();
	//virtual void attack() = 0;
	~Character();
};

#endif
