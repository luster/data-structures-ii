// Ethan Lusterman
// ECE165, Fall 2013
// graph.h

#ifndef _GRAPH_H
#define _GRAPH_H

#include "hash.h"
#include "heap.h"

#include <iostream>
#include <string>
#include <list>
#include <climits>

class graph {

  public:

    // The constructor creates the graph by initializing the hashTable of vertices
    graph(int capacity=100);

    // Insert a vertex into the graph with string id
    bool insertVertex(std::string id);

    // Check if a particular vertex exists in the graph
    bool checkVertex(std::string id);

    // Insert an edge with given start and end string ids with cost dist
    bool insertEdge(std::string start, std::string end, int dist);

    // Dijkstra's algorithm
    void runDijkstra(std::string sourceVertex);

    // Write the output file
    void writeOut(std::string filename);

  private:
    class edge;

    // nested vertex class
    class vertex {
      public:
        std::string id;
        bool isKnown;
        int dist;
        std::list<edge> adj;
        vertex *prev;
    };

    class edge {
      public:
        int cost;
        vertex *destination;
    };


    std::list<vertex *> vertices;
    hashTable *vertex_map;
};

#endif //_GRAPH_H
