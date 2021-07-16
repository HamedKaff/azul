#ifndef BOX_LID_H
#define BOX_LID_H

#include "LinkedList.h"
#include "Tile.h"

class BoxLid{
    public:
        BoxLid();
        ~BoxLid();
        
        //Adds singular
        void add(Tile* tile);
        //draw singular
        Tile* withdraw();
        //getter
        int size();
        string toString();

    private:
    LinkedList* lid;
    int numTiles;
};


#endif //BOX_LID_H