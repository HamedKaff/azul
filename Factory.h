#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <vector>

#include "Tile.h"

using std::vector;
using std::string;

class Factory{
	public:
		Factory();
		Factory(Tile* tile, int number);
		~Factory();
		 Factory(int number);
		 Tile* FTile();
		Tile firstToken(int i);
		void removefirstToken(int i);





		void fillFactory(Tile* tile, unsigned int factNum);

		//Returns true if more tiles to return of that colour.
		vector<Tile*> drawFromFactory(Tile* colour, unsigned int factNum,  int centrFact);
		//returns the number of tiles of a given colour in a given factory
		bool containsColour(Tile* colour, unsigned int factNum);
		string toString();
		string displayFactories();
		bool checkEmpty();
		int factorySize();

	

	private:
 		vector<vector<Tile*>> factories = vector<vector<Tile*>>();

};

#endif //FACTORY_H
