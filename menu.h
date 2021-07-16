#ifndef AZUL_MENU_H
#define AZUL_MENU_H


#include <limits>

#include "TestLoadGame.h"
#include "LinkedListTest.h"
#include "Game.h"
#include "mosaicTesting.h"
#include "TestTile.h"
#include <stdlib.h>


 //int numPlayers;

int displayMenu();
  int menu();

  int getFactNum();
   

void newGameSetup();
void loadGame();
int getPlayerNum();
int getFactNumber();
int getPlayerNum();




void displayCredits();
void testMenu();
void testLoadMenu();
std::string getName(int number);
bool checkNumPlayers(std::string input);

 
bool checkFactoris(std::string input);
 

#endif //AZUL_MENU_H
