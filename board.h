#ifndef __BOARD_H__
#define __BOARD_H__
#include <string>

class Board {
    std::string file;
    std::string *map; // array for storage of the map rows

    void createBoard();
    public:
        Board(std::string filename = "");
        ~Board();
        void printBoard();
        char getLocation(int row, int col);
        void modifyLocation(int row, int col, char change);
};

#endif
