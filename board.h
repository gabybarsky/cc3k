#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include <vector>
#include "chamber.h"
#include "players/player.h"

class Board {
    std::string file;
    std::string *map; // array for storage of the map rows
    Chamber **chambers;

    void createBoard();
    void generateFloor();
    char playerSelect();
    void commitMove(char moveTile, std::vector<int> prevPos, std::vector<int> newPos);
    void modifyChamber(std::vector<int> newPos);
    public:
        Player *player;

        Board(std::string filename = "");
        ~Board();
        void printBoard();
        char getLocation(int col, int row);
        void modifyLocation(int col, int row, char change);
        void moveFloor();
        int getCurrentFloor();
        void makePlayer();
        void updatePlayer(std::string direction);
};

#endif
