#ifndef __CHAMBER_H__
#define __CHAMBER_H__

class Board;

class Chamber {
    int id;
    int floor;
    int topRow, topCol;
    int width, height;
    bool **validTile;
    Board *board;

    void assignValids();
    public:
        Chamber(int id, int floor, Board* board);
        ~Chamber();
        bool isValidTile(int col, int row);
        int getTopCol();
        int getTopRow();
        int getWidth();
        int getHeight();
        void generateChamber();
        void generatePlayer(char race);
};
#endif
