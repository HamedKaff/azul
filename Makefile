.default: all

all: aptAss2

clean:
	rm -f aptAss2 *.o

aptAss2: menu.o Tile.o LinkedList.o Node.o LinkedListTest.o Game.o Bag.o BoxLid.o Factory.o Player.o StorageRows.o Wall.o BrokenTiles.o  TestTile.o TestLoadGame.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^