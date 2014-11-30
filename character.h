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
	int maxHp;
	char symbol;
    std::vector<int> position;
    char prevTile;
	std::string race;
	
 public:
	Character(int hp, int atk, int def, char sym, std::vector<int> &pos, std::string race);
	//virtual void onTurn() = 0;
	int getAtk();
	int getDef();
	int getHp();
	char getSymbol();
    std::vector<int> getPosition();
    char getPrevTile();
    virtual void setPrevTile(char tile);
	std::string getRace();
	void addHp(int amt);
	//virtual void attack() = 0;
	virtual ~Character() = 0;
};

#endif
