// Ethan Lusterman
// ECE165, Fall 2013

#include <iostream>
#include "heap.h"

using namespace std;


heap::heap(int capacity) {
    data.resize(capacity+1);
    mapping = new hashTable(capacity*2);
}

int heap::insert(const std::string &id, int key, void *pv) {
}


int heap::setKey(const std::string &id, int key) {
}


int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
}


int heap::remove(const std::string &id, int *pKey, void *ppData) {
}


void heap::percolateUp(int posCur) {
}

void heap::percolateDown(int posCur) {
}

int heap::getPos(node *pn) {

    int pos = pn - &data[0];
    return pos;
}

// delarations of data vector and hash table pointer
//      std::vector<node> data; // the actual binary heap
//      hashTable *mapping; // maps ids to node pointers
// part of heap constructor
//      data.resize(capacity+1);
//      mapping = new hashTable(capacity*2);
// an example of a call to the hash table's getPointer member function
//      mapping -> setPointer(data[posCur].id, &data[posCur]);
// an example of a call to the hash table's getPointer member function
//      node *pn = static_cast<node *> (mapping->getPointer(id, &b));
// filling in ppData in deleteMin
//      *(static_cast<void **> (ppData)) = data[1].pData;
