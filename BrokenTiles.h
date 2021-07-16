#ifndef BROKEN_TILES_H
#define BROKEN_TILES_H

#include <string>
#include "Tile.h"
#include "BoxLid.h"
#include <vector>

using std::string;

#define DEDUCT_ONE 1
#define DEDUCT_TWO 4
#define DEDUCT_THREE 6


class BrokenTiles{
private:

    int finalScore;
    BoxLid* lid = nullptr;

     Tile* brokenTile[7];
     int tilesInFloor;

   

public:
    BrokenTiles(BoxLid* lid);
    ~BrokenTiles();

    //if brokentile  array is full.
    bool  isFull();

    //  these  to methods may  need  to  be  added  somewhere else in other classes 
    //probably the player class
    void resetPoints();
    int getPoints();

    void isPlaceViable(Tile* t, int  row);

    void addToBrokenTile(Tile* t);

    int endRound();

    //regarding save/load functions
    void loadToBrokenTile(Tile* t);

    int deductedPoints();

    string toString();
 
};

#endif