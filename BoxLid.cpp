#include "BoxLid.h"

BoxLid::BoxLid(){
    this->lid = new LinkedList();
    this->numTiles = 0;
}

BoxLid::~BoxLid(){
    lid->clear();
    delete lid;
    lid=nullptr;
}

void BoxLid::add(Tile* tile){
    lid->addFront(tile);
    numTiles++;
}

//draw singular
Tile* BoxLid::withdraw(){
    if(numTiles != 0){
        numTiles--;
    }
    return lid->retrieveFront();
}
//getter
int BoxLid::size(){
    return numTiles;
}

string BoxLid::toString(){
    string toReturn = "";
    for(int i = 0; i< this->numTiles; ++i){
        toReturn += lid->get(i)->toString();
    }
    return toReturn;
}