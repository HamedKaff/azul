#include "Player.h"

Player::Player(int playerNumber, string playerName, int score, BoxLid* boxlid){
    this->playerID = playerNumber;
    this->playerName = playerName;
    this->score = score;
    this->boxlid = boxlid;
    this->storageRows = new StorageRows(boxlid);
    this->wall = new Wall();
    this->brokenTiles = new BrokenTiles(boxlid);
}

Player::~Player(){

    if(storageRows != nullptr){
        delete storageRows;
    }
    storageRows = nullptr;


    if(wall != nullptr){
        delete wall;
    }
    wall = nullptr;


    if(brokenTiles != nullptr){
        delete brokenTiles;
    }
    brokenTiles = nullptr;

    //Does not own the boxlid. The game class will delete that.
}

void Player::placeTiles(vector<Tile*> draw, int chosenStorageRow){
    for(Tile * tile : draw){
        if(tile != nullptr){
            if(tile->equals(Tile('F'))){
                brokenTiles->addToBrokenTile(tile);                
            }
            else{
                if(chosenStorageRow == 6){
                    brokenTiles->addToBrokenTile(tile);
                }
                else{
                    if(!storageRows->ifRowIsComplete(chosenStorageRow)){
                        this->storageRows->addToRow(tile, chosenStorageRow);
                    }
                    else{
                        brokenTiles->addToBrokenTile(tile);
                    }
                } 
            }
        }
    }
}

StorageRows *Player::getStorageRows() {
    return storageRows;
}

bool Player::checkStorageRowValid(int row, Tile* colour)
{
    bool toReturn = false;
    if(row == 6){
        toReturn = true;
    }
    else{
        if(0 <= row && row < 6){
            toReturn = this->storageRows->ifRowIsViable(colour, row, this->wall);
        }
    }
    return toReturn;
}

//      1. Move full storage rows to wall, 
//      2. increase points by return value
//      3. Move broken tiles to boxlid and decrement player points
//      4. Return a bool for whether a row or column has been completed (which would end the game)
bool Player::endRound(){
    vector<Tile*> draw = vector<Tile*>();
    //move full storage rows to wall / boxlid
    for(unsigned int i = 0; i < 5; ++i){
        if(this->storageRows->ifRowIsComplete(i)){
            draw = storageRows->getStorageRow(i);
            for(unsigned int j = 0; j < draw.size(); ++j){
                if(j == 0){
                    this->score += wall->addToWall(draw[j], i);
                }
                else{
                    boxlid->add(draw[j]);
                }
            }
        }
    }
    // Handle broken tiles
    score += brokenTiles->endRound();
    if(score < 0){
        score = 0;
    }
    return wall->linesComplete();
}

string Player::displayMosaic(){
    string toReturn = "Mosaic for Player: " + this->playerName + "\n";
    for(int i = 0; i<5; ++i){
        toReturn += std::to_string(i) + ":" + storageRows->printRow(i) + "||" + wall->stringRow(i);
        toReturn += "\n";
    }
    //cout << brokenTiles->toString();
    (toReturn.append("Broken: ")).append(brokenTiles->toString());
    
    return toReturn;
}
//retreving information
string Player::getName(){
    return this->playerName;
}

int Player::getScore(){
    return this->score;
}

int Player::getID(){
    return this->playerID;
}

string Player::mosaicToString(){
    string toReturn = "";
    toReturn += storageRows->toString() + "\n" + wall->toString() + "\n" + brokenTiles->toString();
    return toReturn;
}

string Player::playerToString(){
    string toReturn = "";
    toReturn += playerName + "\n" + std::to_string(score);
    return toReturn;
}

//Must handle nullptrs
void Player::loadStorageRows(Tile* tile, int row){
    if(tile != nullptr && tile->getEnum()!= nullptr){
        this->storageRows->addToRow(tile, row);
    }
}
//Must handle nullptrs
void Player::loadWall(Tile* tile, int row, int col){
    if(tile != nullptr &&  tile->getEnum()!= nullptr && wall->isPlaceViable(tile, row)){
        wall->addToWall(tile, row);
    }
}
//Must handle nullptrs
void Player::loadBrokenTiles(Tile* tile){
    if(tile != nullptr && tile->getEnum()!= nullptr){
        this->brokenTiles->addToBrokenTile(tile);
    }
}