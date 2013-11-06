// Ethan Lusterman
// ECE165, Fall 2013

#include <iostream>
#include "heap.h"

using namespace std;

heap::heap(int capacity) {
    this->capacity = capacity;
    this->filled = 0;
    data.resize(capacity+1);
    mapping = new hashTable(capacity*2);
}

int heap::insert(const std::string &id, int key, void *pv) {
    if (filled == capacity)
        return 1;

    else if (filled < capacity && mapping->contains(id))
        return 2;

    else {
        if (filled == capacity - 1)
            data.resize(capacity*2);

        filled++;

        // insert node into heap
        data[filled].id = id;
        data[filled].key = key;
        data[filled].pData = pv;

        // insert id and pointer into hashtable
        mapping->insert(id, &data[filled]);

        // percolate up
        percolateUp(filled);

        return 0;
    }
}


int heap::setKey(const std::string &id, int key) {
    bool keyExists = false;
    node *pn = static_cast<node *> (mapping->getPointer(id, &keyExists));

    if (!keyExists)
        return 1;

    int nodePos = getPos(pn);

    data[nodePos].key = key;

    bool percDown;
    percDown = ((nodePos*2 <= filled ) && (data[nodePos].key > data[nodePos*2].key)) || \
               ((nodePos*2+1 <= filled) && (data[nodePos].key > data[nodePos*2+1].key)) || \
               (nodePos == 1);
    // percolate up or down if heap order property violated
    // if (data[nodePos].key > data[nodePos*2].key || data[nodePos].key > data[nodePos*2+1].key || nodePos == 1)
    if (percDown)
        percolateDown(nodePos);
    else if (data[nodePos].key < data[nodePos/2].key)
        percolateUp(nodePos);

    return 0;
}


int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
    if (filled == 0)
        return 1;

    // set optional pointers
    if (pId)
        *pId = data[1].id;
    if (pKey)
        *pKey = data[1].key;
    if (ppData)
        *(static_cast<void **> (ppData)) = data[1].pData;

    // remove string from hashtable
    mapping->remove(data[1].id);

    // overwrite first item with last and percolate down
    data[1] = data[filled];
    filled--;
    percolateDown(1);
    return 0;
}


int heap::remove(const std::string &id, int *pKey, void *ppData) {
    bool exists = false;
    node *pn = static_cast<node *> (mapping->getPointer(id, &exists));

    if (!exists)
        return 1;

    int nodePos = getPos(pn);

    // set optional pointers
    if (pKey)
        *pKey = data[nodePos].key;
    if (ppData)
        *(static_cast<void **> (ppData)) = data[nodePos].pData;

    // remove id from hashtable
    mapping->remove(id);

    // overwrite nodePos with last element, set new pointer,
    data[nodePos] = data[filled];
    mapping->setPointer(data[nodePos].id, &data[nodePos]);
    filled--;

    // check heap order property and percolate up or down if necessary
    bool percDown;
    percDown = ((nodePos*2 <= filled ) && (data[nodePos].key > data[nodePos*2].key)) || \
               ((nodePos*2+1 <= filled) && (data[nodePos].key > data[nodePos*2+1].key)) || \
               (nodePos == 1);
    //if (data[nodePos].key > data[nodePos*2].key || data[nodePos].key > data[nodePos*2+1].key || nodePos == 1)
    if (percDown)
        percolateDown(nodePos);
    else if (data[nodePos].key < data[nodePos/2].key)
        percolateUp(nodePos);

    return 0;

}


void heap::percolateUp(int posCur) {
    int hole = posCur;
    node tmp = data[posCur];

    for ( ; hole > 1 && tmp.key < data[hole/2].key; hole /= 2) {
        data[hole] = data[hole/2];
        mapping->setPointer(data[hole].id, &data[hole]);
    }

    data[hole] = tmp;
    mapping->setPointer(data[hole].id, &data[hole]);
}

void heap::percolateDown(int posCur) {
    int child;
    int hole = posCur;
    node tmp = data[posCur];

    for ( ; hole * 2 <= filled; hole = child) {
        child = hole * 2;
        if (child != filled && data[child+1].key < data[child].key)
            child++;
        if (data[child].key < tmp.key) {
            data[hole] = data[child];
            mapping->setPointer(data[hole].id, &data[hole]);
        }
        else
            break;
    }
    data[hole] = tmp;
    mapping->setPointer(data[hole].id, &data[hole]);
}

int heap::getPos(node *pn) {
    int pos = pn - &data[0];
    return pos;
}
