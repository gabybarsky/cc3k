#ifndef __CHAMBER_H__
#define __CHAMBER_H__
#include <vector>

class Board;

class Chamber {
    int id;
    int topRow, topCol;
    int width, height;
    bool **validTile;
    Board *board;

    void assignValids();
    public:
        Chamber(int id, Board *board);
        ~Chamber();
        bool isValidTile(int col, int row);
        void setValid(int col, int row, bool valid);
        int getTopCol();
        int getTopRow();
        int getWidth();
        int getHeight();
        std::vector<int> generatePosition();
        void generateStairs();
        void generateChamber();
        void generatePlayer(char race);
        bool isWithin(int x, int y);
};
#endif
