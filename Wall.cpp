#include "Wall.h"


Wall::Wall(){
    gameOver = false;
    for (int i = 0; i < WALL_DIM; i++){
        for (int j = 0; j < WALL_DIM; j++){
            wall[i][j] = nullptr;
        }
    }
}

Wall::~Wall() {
    for (int i = 0; i < WALL_DIM; i++) {
        for (int j = 0; j < WALL_DIM; j++) {
            if(wall[i][j] != nullptr){
                delete wall[i][j];
            }
            wall[i][j] = nullptr;
        }
    }
}

int Wall::addToWall(Tile* tile, int row) {

    /*
     * the  row number and the  tile location (colPos = 2 + row)  are proportional
     * meaning that  if row  was 1, then we  add  2 which equals 3  and which is the
     * correct  location of  the tile on the  Wall
     */

    int colPos = 0;
    //enum Tile{R,Y,B,L,U,F};

    if (*(tile->getEnum()) == R) {
        colPos = 2 + row;

    } else if (*(tile->getEnum()) == Y){

        colPos = 1 + row;
    } else if (*(tile->getEnum()) == B){

        colPos = 0 + row;
    } else if (*(tile->getEnum()) == L){

        colPos = 4 + row;
    } else if (*(tile->getEnum()) == U){

        colPos = 3 + row;
    }

    colPos = colPos % WALL_DIM;

    wall[row][colPos] = tile;

    int finalScore = 0; 
    finalScore = calcScore(row, colPos);

    return finalScore;
}

bool Wall::isPlaceViable(Tile* t, int row){
    bool viable = true;

    for (int i = 0; i < WALL_DIM && viable; i++){
        if(
            (wall[row][i] != nullptr) &&
            ( wall[row][i]->equals(t))
        ) viable = false;
    }
    return viable;
}

bool Wall::linesComplete(){
    return gameOver;
}

/*
* this function is going to check horizontally of the specific coordinate
* and will check if there any consecutive tiles.
* we can call this function later on to check if a row is complete to trigget game win
* and this happens if the function returns 5 at least, which it  wouldn't return until there is 5 tiles in that row.
* and this may apply as well for the vertical  check function below.
*/
int Wall::checkHorizontalAdj(int row, int col){

    int score = 0;
    // this will count the current tile as we scan left
    int iterator = col;
    bool flag = true;
    // scan left
    while (iterator >= 0 && flag){
        if (wall[row][iterator] != nullptr)
            score++;
        else flag = false;
        iterator--;
    }

    flag = true;
    // this will not count the current tile as we scan right
    iterator = col + 1;
    // scan right
    while (iterator < WALL_DIM && flag){
        if (wall[row][iterator] != nullptr)
            score++;
        else flag = false;
        iterator++;
    }
	
    if(score == 5){
        gameOver = true;
		score+= 2;
	}
    return score;
}


//this function is going to  check vertically of  the  specific coordinate
//and  will check if  there  any consecutive tiles.
int Wall::checkVerticalAdj(int row, int col){

    int score = 0;
    // this will count the current tile as we scan below
    int iterator = row;
    bool flag = true;
    // scan below
    while (iterator >= 0 && flag){
        if (wall[iterator][col] != nullptr)
            score++;
        else flag = false;
        iterator--;
    }

    flag = true;
    // this will count the current tile as we scan above
    iterator = row + 1;
    // scan above
    while (iterator < WALL_DIM && flag){
        if (wall[iterator][col] != nullptr)
            score++;
        else flag = false;
        iterator++;
    }

	if(score ==   1){
		score = 0;
	}
	if(score == 5){
	   score+= 7;
	}

	//if score  =  1  set  it to 0
	//checkif score  =  5 add  7  pts
    return score;
}

std::string Wall::toString(){

std::string string = "";

for(int  i = 0; i< WALL_DIM; ++i){
	if(i !=  0){
		string += "\n";
	}
	for(int j  =  0;  j  < WALL_DIM; j++){
		if(wall[i][j] != nullptr){
		string += wall[i][j]->toString();
		}
        else{
			string += ".";
		}
	 }
   }
   return  string;
}

//apply and setting colours of the wall 
string Wall::stringRow(int row){
    string toReturn = "";
    for(int i = 0; i< WALL_DIM; ++i){
        if (row==0) {
            if (i==0) toReturn+="\033[34m"; 
            if (i==1) toReturn+="\033[33m"; 
            if (i==2) toReturn+="\033[31m";
            if (i==3) toReturn+="\033[30m";
            if (i==4) toReturn+="\033[36m";
        }
        if (row==1) {
            if (i==0) toReturn+="\033[36m";
            if (i==1) toReturn+="\033[34m"; 
            if (i==2) toReturn+="\033[33m"; 
            if (i==3) toReturn+="\033[31m";
            if (i==4) toReturn+="\033[30m";
        }
        if (row==2) {
            if (i==0) toReturn+="\033[30m";
            if (i==1) toReturn+="\033[36m";
            if (i==2) toReturn+="\033[34m"; 
            if (i==3) toReturn+="\033[33m"; 
            if (i==4) toReturn+="\033[31m";
        }
        if (row==3) {
            if (i==0) toReturn+="\033[31m";
            if (i==1) toReturn+="\033[30m";
            if (i==2) toReturn+="\033[36m";
            if (i==3) toReturn+="\033[34m"; 
            if (i==4) toReturn+="\033[33m"; 
        }
        if (row==4) {
            if (i==0) toReturn+="\033[33m"; 
            if (i==1) toReturn+="\033[31m";
            if (i==2) toReturn+="\033[30m";
            if (i==3) toReturn+="\033[36m";
            if (i==4) toReturn+="\033[34m"; 
        }
        if(wall[row][i] != nullptr){
           toReturn += wall[row][i]->toString();
        }
        else{
            toReturn += ".";
        }
         
    }
    toReturn += "\033[37m"; 
    return toReturn;
}
//one function  for the  10 points
//one for the check calc

/*
* This function is going to return 10 points if alltiles from the same color exist
* the apporach taken is to have an  int array of size 5, and setting each tile type
* to an index and increment however many times the tile type appears. and returns a value
* from  0 to 50. (0, 10, 20, 30, 40, 50).
*/
int Wall::AllTilesOfTypeExist(){
    int pts = 0;
    int tiles[5]  = {};

    //Y B R L U
    for(int i =  0; i < WALL_DIM; i++){
        for(int j = 0; j < WALL_DIM; j++){

            if(wall[i][j]  !=  nullptr ){
                if(*(wall[i][j]->getEnum()) == Y){
                    tiles[0] += 1;
                }
                if(*(wall[i][j]->getEnum()) == B){
                    tiles[1] +=1;
                }
                if(*(wall[i][j]->getEnum()) == R){
                    tiles[2] +=1;
                }
                if(*(wall[i][j]->getEnum()) == L){
                    tiles[3] +=1;
                }
                if(*(wall[i][j]->getEnum()) == U){
                    tiles[4] +=1;
                }
            }
        }
    }

    for(int i =0; i < 5; i++){
        if(tiles[i]  ==  WALL_DIM){
            pts  = pts + 10;
        }
    }

    return pts;

}

int Wall::calcScore(int row, int col){
  int score = 0;
  int FiveTileScore  = 0;
  int horizontalScore = 0;
  int verticalScore = 0;

  FiveTileScore  = AllTilesOfTypeExist();
  
  horizontalScore = checkHorizontalAdj(row,col);
  if(horizontalScore > 1){
      score  +=  horizontalScore;
    }

  verticalScore = checkVerticalAdj(row,  col);
    if(verticalScore > 1){
        score  +=  verticalScore;
    }
    
    if(score == 0){
    score = 1;
    }

  score +=  FiveTileScore;

  return score;
}