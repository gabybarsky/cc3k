#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>
#include "chamber.h"
#include "players/player.h"

class Board {
    std::string file;
    std::string **map; // array for storage of the map rows
    int currentFloor;
    Chamber **chambers;

    void createBoard();
    void generateFloor(int floor);
    public:
        Player *player;

        Board(std::string filename = "");
        ~Board();
        void printBoard();
        char getLocation(int row, int col);
        void modifyLocation(int col, int row, int floor, char change);
        void moveFloor();
        int getCurrentFloor();
};

#endif
