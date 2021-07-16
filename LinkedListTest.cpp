#include "LinkedListTest.h"


LinkedListTest::LinkedListTest(){
    cout << "entering test" << endl;
    Tile* tile = new Tile('R');
    cout << "Create?" << endl;
    if(tile != nullptr){
    cout << "Tile R = " << tile->toString();
    }

    cout << "get passed" << endl;

    string expectedVals[7] = {"R","B","U","F","Y","L","."};
    bool tests = true;

    //"Creating List:
    LinkedList list = LinkedList();

    //"Adding Tiles Front:"
    list.addFront(new Tile('L'));
    list.addFront(new Tile('Y')); 
    list.addFront(new Tile('F'));
    list.addFront(new Tile('U'));
    list.addFront(new Tile('B'));
    list.addFront(new Tile('R')); 

    //Testing add Back contents
    for(int i = 0; i < 6; ++i){
        if(list.get(i)->toString() != expectedVals[i]){
            tests = false;
            cout << "Error in add front" << endl;
        }
    }

    //"Removing (front) all but the first tile:"
    int size = list.getSize() - 1;
    for(int i = 0; i < size; ++i){
        list.deleteFront();
    }
    //Checking last remaining tile
    for(int i = 0; i< 6; ++i){
        if(i == 0){
        if(list.get(i)->toString() != expectedVals[5]){
            tests = false;
            cout << "." << endl;
        }
        }
        else{
            if(list.get(i) != nullptr){
              tests = false;
                cout << "Error in delete front" << endl;  
            }
        }
    }
    
    //"Removing (Front) Last Tile"
    list.deleteFront();
    
    //cout << "Deleting (Front) Empty List"
    list.deleteFront();
    //"Checking Empty List"
    if(list.get(0)->toString() != expectedVals[6]){
            cout << "Error in delete front" << endl;
            tests = false;
        }

    //"Adding Tiles (Back):"
    list.addBack(new Tile(R)); 
    list.addBack(new Tile(B));
    list.addBack(new Tile(U));
    list.addBack(new Tile(F));
    list.addBack(new Tile(Y)); 
    list.addBack(new Tile(L));

    //Testing contents
    for(int i = 0; i < list.getSize(); ++i){
        if(list.get(i)->toString() != expectedVals[i]){
            cout << "Error after addback" << endl;
            tests = false;
        }
    }

    //"Removing (back) all but the first tile:"
    int size2 = list.getSize() - 1;
    for(int i = 0; i < size2; ++i){
        list.deleteBack();
    }
    //Checking last remaining tile
    for(int i = 0; i< 6; ++i){
        if(i == 0){
        if(list.get(i)->toString() !=expectedVals[0]){
        tests = false;
        cout << "Error in delete back" << endl;
        }
        }
        else{
            if(list.get(i) != nullptr){
                 tests = false;
            cout << "Error in delete back" << endl;
            }
        }
    }
    
    
    //"Removing (Back) Last Tile"
    list.deleteBack();
    
    //"Deleting (Back) Empty List" << endl;
    list.deleteBack();

    //Checking Empty List
    if(list.get(0)->toString() != expectedVals[6]){
        tests = false;
        cout << "Error in delete back" << endl;
    }

    if(tests == false){
        cout << "\n**Linked List Tests Failed**\n" << endl;
    }
    else{
        cout << "\n**Linked List Tests Passed**\n" << endl;
    }
}