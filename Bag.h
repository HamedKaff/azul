#ifndef BAG_H
#define BAG_H
#include <random>
#include <vector>
#include "LinkedList.h"
#include "Tile.h"

using std::vector;
using std::string;

//Author Cameron
class Bag{
    public:
        Bag();
        ~Bag();
        //randomises contents 
        void fillRandomly(vector<Tile*> tiles);

        //Fill from save (Not random)
        void fillFromSave(Tile* tile);
        //draw singular
        Tile* draw();
        int size();
        string toString();

    private:
        LinkedList* list;
        int numTiles;
};


#endif //BAG_H