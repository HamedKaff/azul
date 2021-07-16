#include <string>

#include "BrokenTiles.h"

#include <vector>


BrokenTiles::BrokenTiles(BoxLid* lid) {
    this->lid = lid;
    finalScore = 0;
    tilesInFloor = 0;
    for (int i = 0; i < 7; i++) {
        brokenTile[i] = nullptr;
    }
}

BrokenTiles::~BrokenTiles() {

    for (int i = 0; i < 7; i++) {
        if(brokenTile[i] != nullptr){
            delete brokenTile[i];
        }
        brokenTile[i] = nullptr;
    }
}

void BrokenTiles::addToBrokenTile(Tile * t) {

        bool flag = true;
        for (int i = 0; i < 7 && flag; i++){
          if(brokenTile[i] == nullptr){
            brokenTile[i] = t;
            tilesInFloor++;
            flag = false;
          }      
        }
        if (flag== true){
           lid->add(t);
        }         
        //if added = false, meaning there exceeding number of tiles to be put in the brokentile,
        //then add them to the BoxLid.
      
}

bool BrokenTiles::isFull() {
    bool full = true;

    for (int i = 0; i < 7 && full; i++) {
        if (brokenTile[i] == nullptr) {
            full = false;
        }
    }
    return full;
}

void BrokenTiles::resetPoints() {
    finalScore = 0;
}

int BrokenTiles::getPoints() {
    return finalScore;
}



int BrokenTiles::deductedPoints() {
    // -1   -1   -2   -2   -2   -3   -3

    for (int i = 0; i < 7; i++) {

        if (brokenTile[i] != nullptr) {
            //index 0 and 1 are set to -1 points
            if (i <= DEDUCT_ONE) {
                finalScore -= 1;
            }
            //index 2, 3  and 4 are set to -2 points
            //if i <= index 4 and > 1
            else if (i > DEDUCT_ONE && i <= DEDUCT_TWO) {
                finalScore -= 2;
            }
            //index 5 and 6 are set to -3 points
            //if i <= index 6 and > 4
            else if (i > DEDUCT_TWO && i <= DEDUCT_THREE) {
                finalScore -= 3;
            }

        }
        //points cannot go below 0.
    }
    return finalScore;
}

int BrokenTiles::endRound(){
    int toReturn = deductedPoints();
    resetPoints();

    for(int i = 0; i<7; ++i){
        if(brokenTile[i] != nullptr){
            if(!brokenTile[i]->equals(Tile('F'))){
             lid->add(brokenTile[i]);
                }
            brokenTile[i] = nullptr;
            tilesInFloor--;
        }
    }

    return toReturn;
}

string BrokenTiles::toString(){
    string toReturn = "";
    for(int i = 0; i < 7; ++i){
        if(brokenTile[i] != nullptr){
            toReturn.append(brokenTile[i]->toString());
        }
        else{
            toReturn.append(".");
        } 
    }
    return toReturn;
}