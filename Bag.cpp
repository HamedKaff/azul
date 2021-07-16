#include "Bag.h"
#include <iostream>


//Author: Cameron
Bag::Bag(){
   list = new LinkedList();
   numTiles = 0;
}


Bag::~Bag(){
    list->clear();
    delete list;
    list = nullptr;
}
//randomises contents 
void Bag::fillRandomly(vector<Tile*> tiles){
    /*
        while size > 0
            addFront(rand(0,size-1))  
            if 2 or more elements
                Move the last el to position random
            reduce size by 1.
    */
   int size = tiles.size();
   int position = 0;
   while(size > 0){
        position = rand() % size;
        if(tiles[position] != nullptr){
            list->addFront(tiles.at(position));
        }
        if(size > 1){
           tiles[position] = tiles[size-1];
       }
        size--;
        this->numTiles++;
   }
}
void Bag::fillFromSave(Tile* tile){
    if(tile != nullptr){
        list->addBack(tile);
        numTiles++;
    }
}


Tile* Bag::draw(){
    if(numTiles != 0){
        numTiles--;
    }
    return list->retrieveFront();
}

int Bag::size(){
    return numTiles;
}

string Bag::toString(){
    string toReturn = "";
    for(int i = 0; i< this->numTiles; ++i){
        toReturn += list->get(i)->toString();
    }
    return toReturn;
}