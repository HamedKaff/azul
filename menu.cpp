#include "menu.h"

int numPlayers = -1;
int centralFact = 0;

#define EXIT_SUCCESS 0





int main(int argc, char** argv) {
    int menuSelect = 0;
    bool playing = true;
    // system("color 32");
    //  HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


    while(playing){
    menuSelect = displayMenu();
    
    if(menuSelect == 1){
        newGameSetup();
    }
    if(menuSelect == 2){
        loadGame();
    }
    if(menuSelect == 3){
        displayCredits();
    }
    else if (menuSelect == 4 || menuSelect == 0){
        playing = false;
    }
    else if(menuSelect == 5){
        testMenu();
    }
    }
    return EXIT_SUCCESS;
}

void displayCredits(){
    cout << "------------------------------------" << endl;
    cout << "Name: Cameron van Roon" << endl;
    cout << "Student ID: s3382032" << endl;
    cout << "Email: s3382032@student.rmit.edu.au" << endl;
    cout << "Name: Liangyu Nie" << endl;
    cout << "Student ID: s3716113" << endl;
    cout << "Email: s3716113@student.rmit.edu.au" << endl;
    cout << "Name: Hamed Alkaff" << endl;
    cout << "Student ID: s3708483" << endl;
    cout << "Email: s3708483@student.rmit.edu.au" << endl;
    cout << "-------------------------------------" << endl;
}

int displayMenu(){
    cout << "Menu\n----\n1. New Game\n2. Load Game\n3. Show Student Information\n4. Quit\n5. Tests" << endl;
    int menuSelect = 0;

    bool readSuccess = false;
    do{
        cout << "> ";
        cin >> menuSelect;
        if(cin.good() && menuSelect >= 0 && menuSelect < 5){
            readSuccess = true;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else{
        std::cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(readSuccess == false);
        
    return menuSelect;
}

void testMenu(){
    cout << "TestMenu\n----\n1. Test Linked List\n2. Load Game Test\n3. Mosaic  Test\n4. Tile Test\n0. Quit" << endl;
    int menuSelect = 0;
    bool readSuccess = false;
    do{
        cout << "> ";
        cin >> menuSelect;
        if(cin.good() && menuSelect >= 0 && menuSelect < 5){
            readSuccess = true;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else{
        std::cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(readSuccess == false);
    if(menuSelect == 1){
        LinkedListTest();
    }
    else if(menuSelect == 2){
            testLoadMenu();
        }
   // else if(menuSelect == 3){
      //      mosaicTesting();
      //  }
    else if(menuSelect == 4){
            TestTile();
        }
}

void testLoadMenu(){
    cout << "LoadTestMenu\n----\n1. Test Factories Load\n2. Test Players Load\n3. Test Mosaic Load\n4. Test BagnBox Load\n5. Test Full Load\n0. Quit" << endl;
    int menuSelect = 0;
    bool readSuccess = false;
    do{
        cout << "> ";
        cin >> menuSelect;
        if(cin.good() && menuSelect >= 0 && menuSelect < 6){
            readSuccess = true;
        }
        else{
        std::cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }while(readSuccess == false);
    if(menuSelect == 1){
        TestLoadGame("testFolder1", 1);
    }
    else if(menuSelect == 2){
            TestLoadGame("testFolder1", 2);
        }
    else if(menuSelect == 3){
        TestLoadGame("testFolder1", 3);
    }
    else if(menuSelect == 4){
            TestLoadGame("testFolder1", 4);
        }
    else if(menuSelect == 5){
        TestLoadGame("testFolder1", 5);
    }
}

void newGameSetup(){
    vector<string> playerNames = vector<string>();
    string playername = "";
    string numPlayersString;



    //bool readSuccess = false;

    std::cout << "choose number of players from the following, 2 - 3 - 4 " << std::endl;
    printf(">");
    std::getline(std::cin,numPlayersString);

    while  (!checkNumPlayers(numPlayersString)){
        std::cout<<"Try Again"<<std::endl;
        printf(">");
        std::getline(std::cin,numPlayersString);
    }
    numPlayers = stoi(numPlayersString);

    cout << "> choose either 1 or 2 Central Factories:" << endl; 

    printf(">");
    std::string input;
    std::getline(std::cin,input);

    while  (!checkFactoris(input) ){
        std::getline(std::cin, input);
    }
    centralFact = stoi(input);

    
    std::cout<<"Num Players =" << numPlayers<<std::endl;
    std::cin.clear();
    
    int i = 1;
    while (i<numPlayers +1){
        string name = getName(i);
        playerNames.push_back(name);
        i++;
    }

   // std::cout<<"Player Names are "<<std::endl;
   // std::cout << "getting the number of factories test " << getFactNumber() << std::endl;
   // for(int i=0; i<playerNames.size();i++){
   //     std::cout<<playerNames.at(i)<<std::endl;
   // }int 
    Game(playerNames, numPlayers, centralFact);
}

void loadGame(){
    string fileName;
    bool readSuccess = false;
    cout << "Enter Save Name" << endl;
    while(!readSuccess){
        std::getline(cin, fileName);
        if(cin.good()){
            readSuccess = true;
            Game game = Game(fileName);
        }
    }

}

std::string getName(int number){
    std::cout<<"Enter Player " << number << " name: " <<std::endl;
    std::string name;

   cin>>name;
    if(std::cin.eof()){
        std::cout<<"GoodBye!"<<std::endl;
        exit(1);
    }
    return name;
}


int getFactNumber(){

    return centralFact;
}

int getPlayerNum(){

    return numPlayers;
}


bool checkFactoris(std::string input){
    bool valid = false; 
    if (input != "1" && input != "2")
    {
        cout << "\nInvalid Input! Try Again \t Must Choose 1 OR 2 Center Factories. " << endl;
    }
    else
    {
        int facNum = stoi(input);

        if (facNum == 2 || facNum == 1)
        {
            centralFact = facNum;
            valid = true;
        }
    }
    return valid;

}



bool checkNumPlayers(std::string input){
    bool valid = true;
    if(input != "2" && input != "3" && input != "4"){
        valid = false;
    }
    return valid; 
}