#include  "StorageRows.h"
#include "BrokenTiles.h"



    StorageRows::StorageRows(BoxLid * lid){
      
        for(int i = 0; i  < STORAGE_DIM; i++){
           for(int j = 0; j <= i; j++){
             storageRows[i][j] = nullptr;
            }
        }
    }


    StorageRows::~StorageRows(){
        for(int i = 0; i < STORAGE_DIM;  i++){
            for(int j =  0; j <= i; j++ ){
                if(storageRows[i][j] != nullptr){
                    delete storageRows[i][j];
                }
                storageRows[i][j] = nullptr;
            }
        }
    }

    vector<Tile*>  StorageRows::getStorageRow(int row){
        vector<Tile*> rowTiles  =  vector<Tile*>();
        if(0 <= row && row < STORAGE_DIM){
            for(int i =0; i<= row; i++ ){
                if(storageRows[row][i]!= nullptr){
                    rowTiles.push_back(storageRows[row][i]);
                    storageRows[row][i] = nullptr;
                }
            }  
        }
        return rowTiles;
    }


    void StorageRows::addToRow(Tile * t, int row){

        bool flag = true;
        int row_width = row + 1;

        // instead follow the natural language convetion for C arrays
        for(int i = 0; i < row_width && flag; i++) {
            if ( storageRows[row][i] == nullptr){
                storageRows[row][i] = t;
                flag = false;
            }
        }   
    }

   

    //some sort of method to  tell if there  is  a tile in a  row that is a different color,
    // to  indicate  that  we  cannot place  tiles  in that row
    bool StorageRows::ifRowIsViable(Tile*  t, int row, Wall* w)
    {
        bool viable = true;

        if(ifRowIsComplete(row)){
            viable = false;
        }
        
        if (! w->isPlaceViable(t, row)){
            viable = false;
         }

        // if row 0 is width == 1
        //    row 1 is width == 2
        //    ... and so on
        int row_width = row + 1;
        for (int i = 0; i < row_width && viable;  i++){
             if (
                storageRows[row][i]  !=  nullptr &&
                !storageRows[row][i]->equals(t)) {
                viable = false;
            }
        }
       return viable;
    }

    bool StorageRows::ifRowIsComplete(int row){
        //this  equal boolean value  means if the number of tiles is equal to the row number
        bool equal = false;
        int row_width = row + 1;
        int tilesOnRow = 0;

            for(int j =0; j < row_width; j++){
                if(storageRows[row][j] != nullptr){
                    tilesOnRow++;
                }
            }
            if(row_width == tilesOnRow){
                equal = true;
            }
        
        return equal;
    }

    //added the colours of the tiles when adding to the storage rows
    string StorageRows::printRow(int row){
        string toReturn = "";
        for (int i = 4; i >= 0; --i){
            if(i <= row){
             if(storageRows[row][i] != nullptr){
                string s = storageRows[row][i]->toString();
                if (s[0]=='B') toReturn += "\033[34m";
                if (s[0]=='Y') toReturn += "\033[33m";
                if (s[0]=='L') toReturn += "\033[36m";
                if (s[0]=='U') toReturn += "\033[30m";
                if (s[0]=='R') toReturn += "\033[31m";
                toReturn = toReturn + s;
            }
            else{
                toReturn = toReturn + "\033[33m.";
            }
            }
            else{
                toReturn = toReturn + " ";
            }
        }
        //clear out so to not overwrite 
        toReturn += "\033[37m"; 
        return toReturn;
    }

    string StorageRows::toString(){
        string toReturn = "";
        for (int i = 0; i < 5; ++i){
            if(i != 0){
                toReturn += "\n";
            }
            for (int j = 0; j <= i; ++j){
                if(storageRows[i][j] != nullptr){
                    toReturn = toReturn + storageRows[i][j]->toString();
                }
                else{
                    toReturn = toReturn + ".";
                }
            }
        }
        return toReturn;
    }