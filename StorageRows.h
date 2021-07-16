#ifndef STORAGE_ROWS_H
#define STORAGE_ROWS_H
#include <string>
#include "Tile.h"
#include "BrokenTiles.h"
#include "Wall.h"

#include <vector>
using std::vector;

#define NO_TILE "."

# define STORAGE_DIM 5

class StorageRows{
private:

    Tile * storageRows[STORAGE_DIM][STORAGE_DIM];

 
public:
    StorageRows(BoxLid * lid);
   // StorageRows();


    ~StorageRows();
    //some  methods  may  need to be moved to  private, but all  temporarily  in  public


    //adds tile to the storage rows (can  be  more than one tile!)
    void addToRow(Tile * t, int row);

    //may not  need this method
    void removeFromStorageRow(Tile* t, int row);

    //some sort of method to  tell if there  is  a tile in a  row that is a different color, to  indicate  that  we  cannot place  tiles  in that row
    bool ifRowIsViable(Tile*  t, int row, Wall* w);
    bool ifRowIsComplete(int  row);

   
    //returns a specific Tile from  the StorageRow.
    vector<Tile*>  getStorageRow(int row);

    void loadToStorage(Tile* t, int  x, int y);
    void endOfRound(Wall  w);

    string printRow(int row);
    string toString();

    
};

#endif //STORAGE_ROWS_H