// Ethan Lusterman
// ECE165, Fall 2013

#ifndef _HEAP_H
#define _HEAP_H

#include <vector>
#include <string>
#include "hash.h"

class heap {

    public:

        // The constructor initializes the heap.
        heap(int size = 0);

    private:

        class node {
            public:
                // The id of this node
                std::string id;

                // The key of this node
                int key;

                // A pointer to the actual data
                void *pData;
        };

        void percolateUp(int posCur);

        void percolateDown(int posCur);

        int getPos(node *pn);
};

#endif //_HEAP_H
