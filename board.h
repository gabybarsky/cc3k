#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include <vector>
#include "chamber.h"
#include "items/potion.h"
#include "items/item.h"
#include "items/treasure.h"
#include "items/gold.h"

class Enemy;
class Dragon;
class Player;

class Board {
    std::string file;
    std::string *map; // array for storage of the map rows
    Player *player;
    Chamber **chambers;
	Potion **potions; // array for storage of the potions
	Gold **goldPiles; // array for storage of the gold
	Enemy **enemies; // array for storage of the enemies
	std::vector<Dragon*> dragons; // vector for storage of dragons

    void createBoard();
    void cleanBoard();
    void createPlayer();
    void generateFloor();
    void generateChambers();
    char playerSelect();
	Enemy* generateEnemy(char race);
	void generateEnemies();
	void generatePotions();
	void generateGold();
    void resetGame();
    void updateEnemies();
    void updatePlayer(std::string direction);
    public:
        Board(std::string filename = "");
        ~Board();
        void printBoard();
        char getLocation(int col, int row);
        void modifyLocation(int col, int row, char change);
        void moveFloor();
        void insertPlayer();
	    void makeMerchantsHostile();
	    void updateBoard(std::string direction);
        std::vector<int> generatePosition(int chamber);
        bool isValidTile(int chamber, int col, int row);
        void commitMove(char moveTile, std::vector<int> prevPos, std::vector<int> newPos, Character *c);
	    std::vector<int> generateNearbyPos(std::vector<int> pos, int chamber, bool canBeSame);
        void validateTile(bool valid, std::vector<int> pos, int chamber);
        void pickupGold(std::vector<int> position);
        void modifyChamber(std::vector<int> newPos);
        std::string getPotionName(std::vector<int> position);
};

#endif
