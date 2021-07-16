#ifndef WALL
#define WALL

#include <string>
#include "Tile.h"
#include <vector>


#define WALL_DIM 5


class Wall{
private:
  Tile* wall[WALL_DIM][WALL_DIM];
 
   
public:
    Wall();
    ~Wall();
    std::string toString();


    //add tile to wall
    int addToWall(Tile * t, int row);

    
    bool isPlaceViable(Tile *  t,  int row);
    bool linesComplete();
    void loadToWall(Tile* t, int row,  int col);
    int checkVerticalAdj(int row, int col);
    int checkHorizontalAdj(int row, int col);
    string stringRow(int row);
    int AllTilesOfTypeExist();
    

private:
    bool gameOver;
    int calcScore(int row, int col);
    // int checkLtoR(int xCo, int yCo);
    // int checkRtoL(int xCo, int yCo);
    // int checkToptoBot(int xCo, int yCo);
    // int checkBottoTop(int xCo, int yCo);

 
    
};

#endif