#ifndef TILE_H
#define TILE_H

#include <string>
#include <iostream>
#include "Tile.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

enum TileEnum{R,Y,B,L,U,F};

class Tile{
    public:
        Tile(char tile);
        Tile(std::string colour);
        Tile(Tile* tile);
        ~Tile();
        string toString();
        TileEnum* getEnum();
        void printTile();
        bool equals(Tile* tile);
        bool equals(Tile tile);
        void setColour(std::string colourChar);



    private:
        TileEnum* tile; 


};

#endif //TILE_H 