#include "TestLoadGame.h"




TestLoadGame::TestLoadGame(string folderName, int testType){
    if(testType == 5 || testType == 1){
         string factoriesLocation = "Tests/" + folderName + "/factories.save";
        testLoadFactories(factoriesLocation);
    }
    if(testType == 5 || testType == 2){
        string playersLocation = "Tests/" +  folderName + "/players.save";
        testLoadPlayers(playersLocation);
    }

    if(testType == 5 || testType == 3){
        string mosaicLocation = "Tests/" + folderName + "/mosaic.save";
        testLoadMosaic(mosaicLocation);
    }

    if(testType == 5 || testType == 4){
        string bagnboxLocation = "Tests/" + folderName + "/tilebag_boxlid.save";
        testLoadBagnBox(bagnboxLocation);
    }
    
}

void TestLoadGame::testLoadFactories(string factoriesLocation){
    char c;
    Tile* tile = nullptr;
    
    //Fill factories from save.
    std::ifstream factoriesSave(factoriesLocation);
    //Factory* factory = Factory::getInstance();
    for(int i = 0; i<6; ++i){
        c = 'c';
        while(c != '\n' && factoriesSave.good()){
            factoriesSave.get(c);
            if(c != '\n' && !factoriesSave.eof()){
                tile = new Tile(c);
                tile->printTile();
            }
            else{
                cout << '\n';
            }
        }
    }
    factoriesSave.close();
}

void TestLoadGame::testLoadPlayers(string playersLocation){
    //Player
    std::ifstream playersSave(playersLocation);
    int currentPlayer = -1;
    string playerName;
    int playerScore = -1;
    if(playersSave.good()){
        playersSave >> currentPlayer;
        cout << currentPlayer << endl;
    }
    //clear nl char
    playersSave.clear();
    playersSave.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for(int i = 0; i < NUM_PLAYERS; ++i){
        if(playersSave.good()){
            std::getline(playersSave, playerName);
        }
        if(playersSave.good()){
            playersSave >> playerScore;
        }
        cout << playerName << '\n' << playerScore << endl;
        playersSave.clear();
        playersSave.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    playersSave.close();
}

void TestLoadGame::testLoadMosaic(string mosaicLocation){
    char c;
    Tile* tile = nullptr;
    
    //Fill each player's board.
    std::ifstream mosaicSave(mosaicLocation);
        for(int i =0; i<NUM_PLAYERS; ++i){
            //Fill Storage Rows
            for(int j = 0; j<5; ++j){
                c= 'c';
                while(c != '\n' && mosaicSave.good()){
                    mosaicSave.get(c);
                    if(c != '\n'){
                        tile = new Tile(c);
                        tile->printTile();
                    }
                    else{
                        cout << '\n';
                    }
                }
            }
            //Fill Wall
            for(int j = 0; j<5; ++j){
                if(j != 0){cout << '\n';}
                for(int k = 0; k<5; ++k){
                    if(mosaicSave.good()){
                        mosaicSave.get(c);
                    }
                    else{
                        c = '\n';
                    }
                    if(c != '\n'){
                        tile = new Tile(c);
                        tile->printTile();
                    }
                }
                //clear new-line character
                mosaicSave.clear();
                mosaicSave.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            cout << '\n';
            //Fill BrokenTiles
            do{
                if(mosaicSave.good()){
                    mosaicSave.get(c);
                    if(c != '\n' && !mosaicSave.eof()){
                        tile = new Tile(c);
                        tile->printTile();
                    }
                }
            }while(c != '\n' && !mosaicSave.eof());
            cout << '\n';
        }
        mosaicSave.close();
}

void TestLoadGame::testLoadBagnBox(string bagnboxLocation){
    char c;
    Tile* tile = nullptr;
        
    //Fill bag and boxlid
    std::ifstream bagnboxsave(bagnboxLocation);
    while(bagnboxsave.good()){
        bagnboxsave.get(c);
        if(c!= '\n' && !bagnboxsave.eof()){
            tile = new Tile(c);
            tile->printTile();;
        }
        else{
            cout << '\n';
        }
    }
    while(bagnboxsave.good()){
        bagnboxsave.get(c);
        if(c!= '\n' && !bagnboxsave.eof()){
            tile = new Tile(c);
            tile->printTile();
        }
        else{
            cout << '\n';
        }
    }
    bagnboxsave.close();
}