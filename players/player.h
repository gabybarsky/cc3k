#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "../character.h"
#include <vector>
#include <string>

class Player : public Character {
 protected:
	int gold;
    int floor;
    int chamber;
    std::string race;
    std::string action;
    char prevTile;
 public:
	Player(int hp, int atk, int def, int chamber, std::vector<int> &pos, std::string race);
	virtual ~Player();
    int getFloor();
    int getChamber();
    void setChamber(int chamber);
    void move(std::string direction);
    std::string getRace();
    std::string getAction();
    char getPrevTile();
    void setPrevTile(char tile);
};
#endif
