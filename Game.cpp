#include "Game.h"
#include<string>
 
Game::Game(){
    this->gameBag = new Bag();
    this->boxlid = new BoxLid(); 
    this->players = vector<Player*>();
    this->centralFactories = 0;
}


//Create a new game from scratch
Game::Game(vector<string> playerNames, 
    unsigned int numPlayers, int centrFact): Game(){
    centralFactories = centrFact;
    


    for(unsigned int i = 0; i < numPlayers; ++i){
        players.push_back(new Player(i, playerNames.at(i), 0, this->boxlid));
    }

        //setting the game mode to whether its a 2 central factories or one, and how many players.
        if(this->players.size() == 2){
            this->factories = new Factory(5+centrFact); 
            this->totalFactories = 5+centrFact;
            this->totalPlayers = 2;
        }
        else if(this->players.size() == 3){
            this->factories = new Factory(7+centrFact);
            this->totalFactories = 7+centrFact;
            this->totalPlayers = 3;

        }
        else if(this->players.size() == 4){
        this->factories = new Factory( 9+centrFact);
        this->totalFactories = 9+centrFact;
        this->totalPlayers = 4;

        }

        this->factories = new Factory(new Tile('F'), this->factories->factorySize());

 

    this->currentPlayer = 0;
    getDefaultBag();
    refillFactories();
    gameLoop();
}

//Used when loading from save
Game::Game(string saveName): Game(){
    this->factories = new Factory(totalFactories);
    loadGame(saveName);

    gameLoop();
}


Game::~Game(){
    if(gameBag != nullptr){
        delete gameBag;
        factories = nullptr;
    }
    gameBag = nullptr;
    if(factories != nullptr){
        delete factories;
        factories = nullptr;
    }
    if(boxlid != nullptr){
        delete boxlid;
        boxlid = nullptr;
    }
    

    for(Player* player : players){
        if(player != nullptr){
            delete player;
            player = nullptr;
        }
    }
}

void Game::gameLoop(){
    bool gameOver = false;

    int* chosenRow = new int(-1);
    int* chosenFact = new int(-1);
    int* chosenCentrFact = new int(-1);
    Tile* color = new Tile('F');
  
    
    vector<Tile*> draw = vector<Tile*>();
    bool factoriesEmpty = this->factories->checkEmpty();
    
    while(!gameOver){
        for(Player* player : players){
            cout << "Player " << player->getID() << ": " << player->getName() << " || Score: " << player->getScore() << endl;
        }
        //Round Loop
        while(!factoriesEmpty){
            cout << "Turn for player " << currentPlayer + 1 << endl;
            cout << factories->displayFactories() << endl;
            //Call current player's toString();
            cout << players[currentPlayer]->displayMosaic() << endl;
            
            //play round

            setStorageRows(players[currentPlayer]->getStorageRows() );

            getUserInput(chosenFact, color, chosenRow, this->players[currentPlayer], chosenCentrFact);
            draw = factories->drawFromFactory(color, *chosenFact, *chosenCentrFact);
            players[currentPlayer]->placeTiles(draw, *chosenRow);

            // remove the first F tile in each central factory
            //      if the other first F tile is drawn
            if (draw.front()->equals(Tile('F')) && centralFactories == 2 ) {
                if (*chosenFact == 0 &&
                    factories->firstToken(1).equals(Tile('F')) ) {
                        factories->removefirstToken(1);
                } else 
                if (*chosenFact == 1 &&
                    factories->firstToken(0).equals(Tile('F')) ) {
                        factories->removefirstToken(0);
                } 
            }

            currentPlayer = (currentPlayer + 1) % this->players.size();

           
            factoriesEmpty = this->factories->checkEmpty();
        }

        //End of Round Function
        for(Player* player : players){
            gameOver = player->endRound(); 
        }
        if(factories != nullptr){
            delete this->factories;
            this->factories = nullptr;
        }
        this->factories = new Factory(new Tile('F'), totalFactories);
        refillFactories();
        
        cout << "Bag: " << this->gameBag->toString() << endl;
        cout << "Boxlid: " << this->boxlid->toString() << endl;
        factoriesEmpty = false;
    }
}
//re-fill the factories after the end of the round 
void Game::refillFactories(){
  
    for( int i =centralFactories; i < totalFactories; ++i){
        for(int j =0; j<4; ++j){
            if(gameBag->size() > 0){
                factories->fillFactory(gameBag->draw(), i);
            }
            else{
                refillBag();
            }
        }
    }
}




//getting the user input and returning a vector
 std::vector<string> Game::getUserInput(int* factoryNumber, Tile* colour, int* storageRow, Player* player, int* centrFact){
   string fileName;
   string colorr;
    
    std::string inputFact;
    bool readSuccess = false;
    int cetralFactoryInput =0; 
    std::vector<std::string> inputt;
    int facoryNumberChsosen = 0;
    int storageRowChosen = 0;
    std::cout<<"Enter Command 'turn' OR 'save' OR 'help'"<<std::endl;


    do{
       
    std::vector<std::string> input = getUserInput();
     try{
            facoryNumberChsosen = std::stoi(input[1]);
            storageRowChosen = std::stoi(input[3]);
            colorr = std::string(input[2].c_str());
            
        }
        catch(const std::exception &e){
            cout<<"Catching saving error"<<std::endl;
        }
        catch(...){
            cout<<"Catching saving error"<<std::endl;
        }

        //cout input where to put the remaing
        if (centralFactories == 2 && facoryNumberChsosen != 0 && facoryNumberChsosen != 1)
        {
            cout << "choose which central factory to put your remaining, 0 or 1\n> ";
            std::getline(cin, inputFact);
            while (!checkFactInput(inputFact))
            {
                printf(">");
                std::getline(std::cin, inputFact);
            }
                cetralFactoryInput = std::stoi(inputFact);

            *centrFact = cetralFactoryInput;
        }else {
            *centrFact = 0;
        }
  
        //saving function
        if(input.size()==2 && input[0]=="save"){
            fileName = input[1];
                saveGame(fileName);
                cout << "Game Saved\n>" <<endl;
        }
        else if(input.size()==4 && input[0]=="turn"){
            *factoryNumber = facoryNumberChsosen;
            *storageRow = storageRowChosen;
              colour->setColour(colorr);

            if (colour->getEnum() != nullptr)
            {
                if (this->factories->containsColour(colour, *factoryNumber) && player->checkStorageRowValid(*storageRow, colour))
                {
                    readSuccess = true;
                }
            }
        }

        inputt = input;


    }while(readSuccess == false); 
    return inputt;
}

void Game::refillBag(){
    while(this->boxlid->size() > 0){
        gameBag->fillFromSave(this->boxlid->withdraw());
    }
}

void Game::getDefaultBag(){
    string bagnboxLocation = "DefaultBag-tilebag_boxlid.save";
    vector<vector<Tile*>> bagnbox = loadBagnBox(bagnboxLocation);

    gameBag->fillRandomly(bagnbox[0]);

}

void Game::saveGame(string fileName){
    saveFactories(fileName);
    savePlayers(fileName);
    saveMosaic(fileName);
    saveBagnBox(fileName);

}
//check the central factory input
bool Game::checkFactInput(std::string input){
     bool valid = false; 
   

    if (input == "0" || input == "1")
    {
        valid = true;
    }
    return valid;

}

void Game::saveFactories(string fileName){
    string factoriesLocation = "Tests/" + fileName + "-factories.save";

    std::ofstream saveFile(factoriesLocation);
    saveFile << factories->toString();

    saveFile.close();
}

void Game::savePlayers(string fileName){
    string playersLocation = "Tests/" +  fileName + "-players.save";
    string toPrint = "";
    toPrint += std::to_string(currentPlayer);
    for(Player* player : players){
        toPrint +=  "\n" + player->playerToString();
    }

    std::ofstream saveFile(playersLocation);
    saveFile << toPrint;

    saveFile.close();
}
    
void Game::saveMosaic(string fileName){
        string mosaicLocation = "Tests/" + fileName + "-mosaic.save";

        string toPrint = "";
        for(unsigned int i = 0; i < players.size(); ++i){
            if(i != 0){
                toPrint += "\n";
            }
            toPrint += players[i]->mosaicToString();
        }
        std::ofstream saveFile(mosaicLocation);
        
        saveFile << toPrint;
        saveFile.close();
}

void Game::saveBagnBox(string fileName){
    string bagnboxLocation = "Tests/" + fileName + "-tilebag_boxlid.save";

    std::ofstream saveFile(bagnboxLocation);
    saveFile << gameBag->toString() << "\n" << boxlid->toString();

    saveFile.close();
}

void Game::loadGame(string folderName){
    string factoriesLocation = "Tests/" + folderName + "-factories.save";
    string bagnboxLocation = "Tests/" + folderName + "-tilebag_boxlid.save";
    string playersLocation = "Tests/" +  folderName + "-players.save";
    string mosaicLocation = "Tests/" + folderName + "-mosaic.save";
    
    
    loadFactories(factoriesLocation);

    vector<vector<Tile*>> bagnbox = loadBagnBox(bagnboxLocation);
    //fill bag
    for(unsigned int i = 0; i < bagnbox[0].size(); ++i){
        this->gameBag->fillFromSave(bagnbox[0][i]);
    }
    //fill boxlid
    for(unsigned int i = 0; i < bagnbox[1].size(); ++i){
        this->boxlid->add(bagnbox[0][i]);
    }

    loadPlayers(playersLocation); 
    loadMosaic(mosaicLocation);

}

void Game::loadFactories(string factoriesLocation){
    char c;
    Tile* tile = nullptr;
    //Fill factories from save.
    std::ifstream factoriesSave(factoriesLocation);
   

    totalFactories =0;
    while (!factoriesSave.eof()) {
        c = 'c';
        while(c != '\n' && factoriesSave.good()){
            factoriesSave.get(c);
            if(c != '\n' && !factoriesSave.eof()){
                tile = new Tile(c);
                if(tile->getEnum() != nullptr){
                    factories->fillFactory(tile, totalFactories);
                }    
            }
        }
        totalFactories++;
    }
    factoriesSave.close();
}

void Game::loadPlayers(string playersLocation){
    //Player
    std::ifstream playersSave(playersLocation);
    int currentPlayer = -1;
    string playerName;
    int playerScore = 0;
    if(playersSave.good()){
        playersSave >> currentPlayer;
        this->currentPlayer = currentPlayer;
    }

    
    //clear nl char
    playersSave.clear();
    playersSave.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
    totalPlayers = 0;
    while (!playersSave.eof() ) {
        if(playersSave.good()){
            std::getline(playersSave, playerName);
        }
        if(playersSave.good()){
            playersSave >> playerScore;
        }
        players.push_back(new Player(totalPlayers, playerName, playerScore, this->boxlid));
        //Clear nl char
        playersSave.clear();
        playersSave.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        totalPlayers++;
    }
    playersSave.close();
}

void Game::loadMosaic(string mosaicLocation){
    char c;
    Tile* tile = nullptr;
    
    //Fill each player's board.
    std::ifstream mosaicSave(mosaicLocation);
        for(int i = 0; i<totalPlayers; ++i){
       
            for(int j = 0; j<5; ++j){
                c= 'c';
                while(c != '\n' && mosaicSave.good()){
                    mosaicSave.get(c);
                    if(c != '\n'){
                        tile = new Tile(c);
                        players.at(i)->loadStorageRows(tile, j);
                    }
                }
            }
            //Fill Wall
            for(int j = 0; j<5; ++j){
                for(int k = 0; k<5; ++k){
                    if(mosaicSave.good()){
                        mosaicSave.get(c);
                    }
                    else{

                        c = '\n';
                    }
                    if(c != '\n'){
                        tile = new Tile(c);
                        players.at(i)->loadWall(tile, j, k);
                    }
                }
                //clear new-line character
                mosaicSave.clear();
                mosaicSave.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            //Fill BrokenTiles
            do{
                if(mosaicSave.good()){
                    mosaicSave.get(c);
                    if(c != '\n' ){
                        tile = new Tile(c);
                        players.at(i)->loadBrokenTiles(tile);
                    }
                }
            }while(c != '\n' && !mosaicSave.eof() );
        }
        mosaicSave.close();
}

vector<vector<Tile*>> Game::loadBagnBox(string bagnboxLocation){
    Tile* tile = nullptr;
    char c = '\n';

    vector<vector<Tile*>> bagnbox = vector<vector<Tile*>>();
    bagnbox.push_back(vector<Tile*>());
    bagnbox.push_back(vector<Tile*>());

    //Fill bag and boxlid
    std::ifstream bagnboxsave(bagnboxLocation);
    while(bagnboxsave.good()){
        bagnboxsave.get(c);
        if(c != '\n' && !bagnboxsave.eof()){
            tile = new Tile(c);
            bagnbox[0].push_back(tile);
        }
    }
    while(bagnboxsave.good()){
        bagnboxsave.get(c);
        if(c != '\n' && !bagnboxsave.eof()){
            tile = new Tile(c);
            bagnbox[1].push_back(tile);
        }
    }
    bagnboxsave.close();

    return bagnbox;
}

 //taking the user input
std::vector<std::string> Game::getUserInput(){
  
    std::cout<<">" <<std::endl;
    
    
    std::string userInput = "";
    while (userInput == "")
        std::getline(std::cin, userInput);
    
    while(!validUserInput(userInput)){
        std::getline(std::cin, userInput);
    }

    return splitBySpace(userInput);
}

 void Game::setStorageRows(StorageRows *storageRows) {
    storeRows = storageRows;
 }

 bool Game::validUserInput(std::string str){

    std::vector<string> input = splitBySpace(str);
    bool trueCommand = false;

    //the helper function
    if(input[0]=="help"  ){
        cout << "User help \n" <<
            "  In this part of the game you can \n" <<
            "  issue the command: turn <factory> <Tile> <StorageRow>\n" <<
            "\n" <<
            "      <factory> is a number identifying the factory to draw from\n" <<
            "      <Tile> is a capital letter identifying the tile to draw\n" <<
            "      <StorageRow> is a number identifying row to place the tile into\n\n" ;

     
        for (int i = 0; i< 5; i++) {
            cout << "Storage row #" << i << " is ";
            if (storeRows->ifRowIsComplete(i)) 
                cout << "complete";
            else
                cout << "incomplete";
            cout << "\n";
        }
        cout << "You may place additional tiles in the incomplete rows that have the same color is your chosen\n\n";
      
        cout <<  " if you are left out with tile and there are many of this tile and the row is not enough,\n" <<
                 " just place it in that row and the game will automatically place the remaining in the prokenTiles\n"
                 " however, points will be deducted eventually, and you will be deducted from as the following: \n"
                 " -1   -1   -2   -2   -2   -3   -3 \n\n"  ;

        cout <<  " to win the game, you need to get the most points, not to trigger the game ending,\n" <<
        "which is completing a row in the wall, to get the most points, you can do the following:  \n"
        "if you complete a row you will get 5 points for each tile and 2 points as a bonus \n"
        "if you complete a column you will get 5 points for each tile and 7 points as a bonus \n"
        "if you complete a full 5 tiles in the wall you will get 5 points for each tile and 10 points as a bonus \n";


    
        return false;

    }


    if(input.size()==4){
        bool checkCommand = false;
        bool checkFactory = false;
        bool checkTile = false;
        bool checkStorageRow = false;
        
        
        if(input[0]=="turn"  ){
           checkCommand = true;
        }


        try{
            int factValue =  std::stoi(input[1].c_str());
            if (factValue >= 0 && factValue <= this->totalFactories){
                checkFactory = true;
            }
        }
        catch(const std::exception &e){
            cout<<"Invalid Factory ID try again"<<std::endl;
        }
        catch(...){
            cout<<"Invalid Factory ID try again"<<std::endl;
        }

        //validating the user input for the tile
        if(input[2] == "R" || input[2] == "B" || input[2]== "Y" || input[2] == "L" || input[2] == "U") {
            checkTile = true;
        }
        //validating the user input for the storage row
        if(input[3] == "0" || input[3] == "1" || input[3] == "2" || input[3] == "3" || input[3] == "4"){
            checkStorageRow = true;
        }

        if(checkCommand == true && checkFactory == true && checkTile == true && checkStorageRow == true){
            trueCommand = true;
        }

        
    }
    if(input.size() == 2){
        if(input[0] == "save"){
            trueCommand =true;
        }
    }

    if (!trueCommand) {
        std::cout<<"Invalid Command. Try Again! "<<std::endl;
    }
    return trueCommand;

 } 




std::vector<std::string> Game::splitBySpace(std::string input){
    std::vector<std::string> output;
    std::string str;
    std::stringstream stream(input);

    while(stream >> str){
        output.push_back(str);
    }
    return output;

    
}
