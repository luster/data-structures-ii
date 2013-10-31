// Ethan Lusterman
// ECE165, Fall 2013

#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include "heap.h"

class graph {

  public:

    // The constructor herka derka
    graph(int capacity);

    // Dijkstra's algorithm
    void dijkstra();


  private:
    // nested node class
    class node {
      public:
        string id;
    };

    // dem data members


    // and shit
};

#endif //_GRAPH_H
