#ifndef GAME_H
#define GAME_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "Tile.h"
#include "Factory.h"
#include "Player.h"
#include "BoxLid.h"
#include "Bag.h"

#define NUM_PLAYERS 2

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;

class Game{
private:
  //  Tile* tiles;
  Factory* factories;
  BoxLid* boxlid;
  Bag* gameBag;
  vector<Player*> players;
  int currentPlayer;
  int centralFactories = 0;
  int totalFactories = 0;
  int totalPlayers = 0;



public:
    //Used to initialise base variables
    Game();
    int calcFactories();
    void delFirstToken(); //priv


    //Called when initialising a game from scratch
    Game(vector<string> playerNames, unsigned int numPlayers, int centrFact);

    //Called when loading a game
    Game(string saveName);

    ~Game();

    //increment when checking winning tiles in  the wall   
    int points;

    
    void loadGame(string folderName);
    void setStorageRows(StorageRows *storageRows);
    private:

        //Check if a player has completed a row of 5 or column of 5
        bool EndingGame();

        void gameLoop();
        void getDefaultBag();
        void refillFactories();
        void refillBag();

        void printPlayerState(Player* currentPlayer);
        std::vector<string> getUserInput(int* factoryNumber, Tile* colour, int* storageRow, Player* player, int* centrFact);
        bool checkFactInput(string input);

        void loadFactories(string factoriesLocation);
        void loadPlayers(string playersLocation);
        void loadMosaic(string mosaicLocation);
        vector<vector<Tile*>> loadBagnBox(string bagnboxLocation);

        void saveGame(string fileName);
        void saveFactories(string filename);
        void savePlayers(string filename);
        void saveMosaic(string filename);
        void saveBagnBox(string filename);
        
        bool validUserInput(std::string str);
        
        std::vector<std::string> getUserInput();

        std::vector<std::string> splitBySpace(std::string input);
        StorageRows *storeRows;

    
};


#endif //GAME_H