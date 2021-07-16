#include "Tile.h"

using std::string;
using std::cin;
using std::cout;
using std::endl;

Tile::Tile(char colour){
    tile = nullptr;
    if(colour == 'R'){
        tile = new TileEnum(R);                
    }
    else if(colour == 'Y'){
        tile = new TileEnum(Y);                 
    }
    else if(colour == 'B'){
        tile = new TileEnum(B);             
    }
    else if(colour == 'L'){
        tile = new TileEnum(L);               
    }
    else if(colour == 'U'){
        tile = new TileEnum(U);             
    }
    else if(colour == 'F'){
        tile = new TileEnum(F);               
    }  
}
Tile::Tile(std::string colour){
    tile = nullptr;
    if(colour == "R"){
        tile = new TileEnum(R);                
    }
    else if(colour == "Y"){
        tile = new TileEnum(Y);                 
    }
    else if(colour == "B"){
        tile = new TileEnum(B);             
    }
    else if(colour == "L"){
        tile = new TileEnum(L);               
    }
    else if(colour == "U"){
        tile = new TileEnum(U);             
    }
    else if(colour == "F"){
        tile = new TileEnum(F);               
    }  
}


Tile::Tile(Tile* other){
    this->tile = other->getEnum();
}

Tile::~Tile(){
    if(tile != nullptr){
        delete tile;
        tile = nullptr;
    }
}

TileEnum* Tile::getEnum(){
    return this->tile;
}

void Tile::setColour(std::string colour){
    if(tile != nullptr){
        delete tile;
    }
    tile = nullptr;
    if(colour == "R"){
        tile = new TileEnum(R);                
    }
    else if(colour == "Y"){
        tile = new TileEnum(Y);                 
    }
    else if(colour == "B"){
        tile = new TileEnum(B);             
    }
    else if(colour == "L"){
        tile = new TileEnum(L);               
    }
    else if(colour == "U"){
        tile = new TileEnum(U);             
    }
    else if(colour == "F"){
        tile = new TileEnum(F);               
    }  
}

bool Tile::equals(Tile* other){
     bool toReturn = false;
    if(other->getEnum() != nullptr){
        if(tile != nullptr){
            if(*tile == *(other->getEnum())){
                toReturn = true;
            }
        }
        } 
        else if(tile == nullptr){
            toReturn = true;
            }
        return toReturn;
}

bool Tile::equals(Tile other){
    bool toReturn = false;
    if(other.getEnum() != nullptr){
        if(tile != nullptr){
            if(*tile == *(other.getEnum())){
                toReturn = true;
            }
        }
    }
    else{
        if(tile == nullptr){
            toReturn = true;
        }
    }
    return toReturn;
}

string Tile::toString(){
    string toReturn = "";
    if (tile != nullptr){
        if(*tile == TileEnum(R)){
            toReturn = "R";                
        }
        else if(*tile == TileEnum(Y)){
            toReturn =  "Y";                
        }
        else if(*tile == TileEnum(B)){
            toReturn =  "B";                
        }
        else if(*tile == TileEnum(L)){
            toReturn =  "L";                
        }
        else if(*tile == TileEnum(U)){
            toReturn =  "U";                
        }
        else if(*tile == TileEnum(F)){
            toReturn =  "F";                
        }
    }
    else{
            toReturn =  ".";
        }
    return toReturn;
    }
        
void Tile::printTile(){
    cout << this->toString();
}

         