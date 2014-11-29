#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include <vector>
#include "chamber.h"
#include "players/player.h"
#include "enemies/enemy.h"
#include "enemies/dwarf.h"
#include "enemies/elf.h"
#include "enemies/halfling.h"
#include "enemies/human.h"
#include "enemies/merchant.h"
#include "enemies/orc.h"
#include "items/potion.h"
#include "items/item.h"

class Board {
    std::string file;
    std::string *map; // array for storage of the map rows
    Chamber **chambers;
	Potion **potions; // array for storage of the potions
	Enemy **enemies; // array for storage of the enemies

    void createBoard();
    void cleanBoard();
    void createPlayer();
    void generateFloor();
    void generateChambers();
    char playerSelect();
    void commitMove(char moveTile, std::vector<int> prevPos, std::vector<int> newPos);
    void modifyChamber(std::vector<int> newPos);
	Enemy* generateHuman();
	Enemy* generateDwarf();
	Enemy* generateHalfling();
	Enemy* generateElf();
	Enemy* generateMerchant();
	Enemy* generateOrc();
	void generateEnemies();
	void generatePotions();
    public:
        Player *player;

        Board(std::string filename = "");
        ~Board();
        void printBoard();
        char getLocation(int col, int row);
        void modifyLocation(int col, int row, char change);
        void moveFloor();
        void insertPlayer();
        void updatePlayer(std::string direction);
};

#endif
