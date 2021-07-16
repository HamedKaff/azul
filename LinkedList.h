#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Node.h"

class LinkedList {

public:
LinkedList();
~LinkedList();

int getSize();
void clear();
Tile* get(int i);

Tile* retrieveFront();


void addFront(Tile* data);
void addBack(Tile* data);

void deleteFront();
void deleteBack();

private:
Node* head;
Node* tail;
int size;

};

#endif //LINKED_LIST_H