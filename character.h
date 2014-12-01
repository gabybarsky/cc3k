#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include <string>
#include <vector>
#include "items/gold.h"

class Board;

class Character {
 protected:
	double atk;
	double def;
	int hp;
	int maxHp;
	char symbol;
    std::vector<int> position;
    std::string race;
    char prevTile;
    Board *board;
 public:
	Character(int hp, double atk, double def, char sym, std::vector<int> &pos, std::string race, Board *board);
    virtual ~Character();
	//virtual void onTurn() = 0;
    virtual void move(std::string direction = "") = 0;
	double getAtk();
	double getDef();
	int getHp();
	char getSymbol();
    std::vector<int> getPosition();
    void setPosition(std::vector<int> pos);
    char getPrevTile();
    virtual void setPrevTile(char tile);
	std::string getRace();
	void addHp(int amt);
	//virtual void attack() = 0;
};

#endif
