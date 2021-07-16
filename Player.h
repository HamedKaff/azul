#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

#include "Factory.h"
#include "StorageRows.h"
#include "Wall.h"
#include "BoxLid.h"
#include "Tile.h"


using std::string;

class Player
{
public:
	Player(int playerNumber, string playerName, int score, BoxLid* boxlid);
	~Player();

	StorageRows *getStorageRows();

	/**Member Function  Begin**/
public:
	//returns true if completed row / colomn i.e. game over.
	bool endRound();
	
	// makes turn
	void placeTiles(vector<Tile*> draw, int chosenStorageRow); 

	//checks if potential turn is valid
	bool checkStorageRowValid(int storageRow, Tile* colour);

	//
	string displayMosaic();


	//**CvR: These methods need to be public in order to load a saved game.**
	//Must handle nullptrs
	void loadStorageRows(Tile* tile, int index);
	//Must handle nullptrs
	void loadWall(Tile* tile, int row, int col);
	//Must handle nullptrs
	void loadBrokenTiles(Tile* tile);
	string getName();
	int getScore();
	int getID();

	string mosaicToString();
	string playerToString();
	

private:	
	//check for rowsIndex conforming to rules


	/**Member Variables Begin**/
private:
	string playerName;
	int playerID;
	int score;
	StorageRows* storageRows;
	Wall* wall;
	BrokenTiles* brokenTiles;
	BoxLid* boxlid;

	/**Variables End**/
};

#endif //PLAYER_H