#include "TestTile.h"

TestTile::TestTile(){
    Tile tiles1[6] = {Tile('R'), Tile('Y'), Tile('B'), Tile('L'), Tile('U'), Tile('F')};
    Tile* tiles2[6] = {new Tile('R'), new Tile('Y'), new Tile('B'), new Tile('L'), new Tile('U'), new Tile('F')};
    for(int i = 0; i<6; ++i){
        cout << tiles1[i].toString();
    }
    cout << "\n";
    for(int i = 0; i<6; ++i){
        cout << tiles2[i]->toString();
    }
    cout << "\n";
    cout << "R = R =" << tiles1[0].equals(tiles2[0]) << endl;
    cout << "R = Y =" << tiles1[0].equals(tiles2[1]) << endl;
    cout << "Test Copy Constructor: " << endl;
    Tile copy = Tile(tiles1[0]);
    cout << copy.toString() << endl;
    cout << "R = R =" << copy.equals(tiles2[0]) << endl;

}