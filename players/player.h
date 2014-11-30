#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "../character.h"
#include "../enemies/enemy.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class Player : public Character {
 protected:
	int gold;
    int floor;
    int chamber;
    std::string action;
    int defaultAtk;
    int defaultDef;
 public:
	Player(int hp, int atk, int def, int chamber, std::vector<int> &pos, std::string race);
	virtual ~Player();
    void upFloor();
    int getFloor();
    int getChamber();
    void setChamber(int chamber);
    void move(std::string direction);
    std::string getAction();
    void addAction(std::string action);
    void setAction(std::string action);
    void setPrevTile(char tile);
    void setPosition(std::vector<int> pos);
    void addGold(int quantity);
    int getGold();
	void addAtk(int amt);
	void addDef(int amt);
    void resetStats();
	int attack(Character *e);
};
#endif
