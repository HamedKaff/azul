#include "Factory.h"
#include <iostream>



Factory::Factory(int number){
    for(int i = 0; i< number; ++i){
        factories.push_back(vector<Tile*>());
    }
}

//a new delegate constructor to deal with the F tiles 
Factory::Factory(Tile* tile, int number): Factory( number){
    
    if(factories.size() % 2 != 0){
        factories[1].push_back(tile);
        factories[0].push_back(tile);

    }else{
        factories[0].push_back(tile);

    }

}

Factory::~Factory(){
    for(unsigned int i = 0; i< factories.size(); ++i){
        factories[i].clear();
    }
}

void Factory::fillFactory(Tile* tile, unsigned int factNum){
    if(factNum <factories.size()){
        if(factNum == 0){
            factories[0].push_back(tile);
        }
        else if(factories[factNum].size() < 4){
            factories[factNum].push_back(tile);
        }
    }
}


vector<Tile*> Factory::drawFromFactory(Tile* colour, unsigned int factNum, int centrFact){

    vector<Tile*> toReturn = vector<Tile*>();
    if(factNum < factories.size()){
        //If selecting middle table and First Tile not taken, take it.
        if(factNum == 0 && factories[0][0] != nullptr){
            toReturn.push_back(factories[0][0]);
            factories[0][0] = nullptr;
     
        }
      
        //Get all the Tiles of that colour to return.
        for(unsigned int i = 0; i < factories[factNum].size(); ++i){
            if(factories[factNum][i] != nullptr  && factories[factNum][i]->equals(colour)){
                toReturn.push_back(factories[factNum][i]);
                factories[factNum][i] = nullptr;
            }
        }

        //Move remainder to either the first middle factory or the second central factory, depending on players selection
        if(factNum != 0){
            for(unsigned int i = 0; i < factories[factNum].size(); ++i){
                if(factories[factNum][i] != nullptr){ 
            
                    if(centrFact == 0){
                        factories[0].push_back(factories[factNum][i]);
                        factories[factNum][i] = nullptr;
                    }else if(centrFact == 1){
                        factories[1].push_back(factories[factNum][i]);
                        factories[factNum][i] = nullptr;
                    }
                }
            }
        }
    } 
    return toReturn;
}


bool Factory::containsColour(Tile* colour, unsigned int factNum){
    bool contains = false;
    unsigned int index = 0;
    if(factNum < factories.size()){
        while(index < factories[factNum].size() && contains == false){
            if(factories[factNum][index] != nullptr && factories[factNum][index]->equals(colour)){
                contains = true;
            }
            ++index;
        }
    }
    return contains;
}

bool Factory::checkEmpty(){
    bool empty = true;
    unsigned int i =0;
    unsigned int j = 0;
    while(i< factories.size() && empty == true){
        j=0;
        while(j<factories[i].size() && empty == true){
            if(factories[i][j] != nullptr){
                empty = false;
            }
            ++j;
        }
        ++i;
    }
    return empty;
}

string Factory::displayFactories(){
    string toReturn = "Factories:";
    for(unsigned int i = 0; i<factories.size(); ++i){
        toReturn += "\n" + std::to_string(i) + ": ";
        for(Tile* tile : factories[i]){
            if(tile != nullptr){
                toReturn += tile->toString() + " ";
            }
        }
    }
    return toReturn;
}

string Factory::toString(){
    string toReturn = "";
    for(unsigned int i = 0; i<factories.size(); ++i){
        if(i != 0){
            toReturn += "\n";
            }
        for(Tile* tile : factories[i]){
            if(tile != nullptr){
                toReturn += tile->toString();
            }
        }
    }
    return toReturn;
}

int Factory::factorySize(){
   return factories.size();
}

//the following functions to deal with F tiles.
Tile Factory::firstToken(int i)
{
    vector<int> toReturn;

    return factories[i][0] ;
    
}

void Factory::removefirstToken(int i) {
    factories[i].erase(factories[i].begin());
    
}
