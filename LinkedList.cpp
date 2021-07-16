#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList(){
    this->head = nullptr;
    this->tail = nullptr;
    this->size = 0;
}

LinkedList::~LinkedList(){
    clear();
};



int LinkedList::getSize(){
    return this->size;
}


void LinkedList::clear(){
    while(this->head != nullptr){
        deleteFront();
    }
}

//Returns nullptr if given an index outside of range or if empty list.
Tile* LinkedList::get(int i){
    Tile* toReturn = nullptr;
    if(i >= 0 && i < this->getSize()){
        Node* current = this->head;
        int counter = 0;
        if(this->head != nullptr){
            while(current->next != nullptr && counter != i){
                current = current->next;
                counter++;
            }
            toReturn = current->tile;
        }
    }
    return toReturn;
}

Tile* LinkedList::retrieveFront(){
    Tile* toReturn = nullptr;
    if(head != nullptr){
        toReturn = head->tile;
        head->tile = nullptr;
        deleteFront();
    }
    return toReturn;
}

void LinkedList::addFront(Tile* tile){
    Node* toAdd = new Node(tile, nullptr, nullptr);
    if(size == 0){
        this->head = toAdd;
        this->tail = toAdd;
    }
    else{
        toAdd->next = this->head;
        this->head->prev = toAdd;
        this->head = toAdd;
    }
    this->size++;
}

void LinkedList::addBack(Tile* tile){
    
    Node* toAdd = new Node(tile, nullptr, nullptr);
    if(size == 0){
        this->head = toAdd;
        this->tail = toAdd;
    }
    else{
        toAdd->prev = this->tail;
        this->tail->next = toAdd;
        this->tail = toAdd;
    }
    this->size++;
}

void LinkedList::deleteFront(){
    if(getSize() != 0){
    Node* toDelete = this->head;

    if(getSize() == 1){
        this->head = nullptr;
        this->tail = nullptr;
    }
    else{
        head = head->next;
        head->prev = nullptr;
    }
    this->size--;
    delete toDelete;
    }
}

void LinkedList::deleteBack(){
    if(getSize() != 0){
    if(getSize() == 1){
        deleteFront();
    }
    else{
        Node* toDelete = tail;
        tail = tail->prev;
        tail->next = nullptr;
        this->size--;
        delete toDelete;
    }
    }
}


