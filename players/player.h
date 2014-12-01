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
#include <map>

class Player : public Character {
 protected:
	int gold;
    int floor;
    int chamber;
    std::string action;
    double defaultAtk;
    double defaultDef;
    std::map<std::string, bool> potionKnowledge;
 public:
	Player(int hp, double atk, double def, int chamber, std::vector<int> &pos, std::string race, Board *board);
	virtual ~Player();
    void upFloor(int chamber);
    int getFloor();
    int getChamber();
    void setChamber(int chamber);
    bool changePosition(std::string direction);
    void move(std::string direction);
    std::string getAction();
    void addAction(std::string action);
    void setAction(std::string action);
    void setPrevTile(char tile);
    void addGold(int quantity);
    int getGold();
    std::string getGoldStr();
	void addAtk(double amt);
	void addDef(double amt);
    void resetStats();
	virtual int attack(Character *e);
	bool isNearby(std::vector<int> other);
    void learnPotion(std::string name);
    bool hasKnowledge(std::string name);
};
#endif
