#ifndef TEST_LOAD_H
#define TEST_LOAD_H

#define NUM_PLAYERS 2

#include <string>
#include <fstream>
#include <vector>
#include <limits>

#include "Tile.h"

class TestLoadGame{

public:
    TestLoadGame(string folderName, int testType);

private:
void testLoadFactories(string factoriesLocation);
void testLoadPlayers(string playersLocation);
void testLoadMosaic(string mosaicLocation);
void testLoadBagnBox(string bagnboxLocation);

};

#endif //TEST_LOAD_H