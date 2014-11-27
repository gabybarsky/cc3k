#ifndef __CHAMBER_H__
#define __CHAMBER_H__

class Board;

class Chamber {
    int id;
    int floor;
    int topRow, topCol;
    int width, height;
    bool **validTile;

    void assignValids();
    public:
        Chamber();
        Chamber(int id, int floor);
        ~Chamber();
        bool isValidTile(int row, int col);
        void generateChamber(Board *board);
};
#endif
