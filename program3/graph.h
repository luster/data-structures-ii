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
#include <fstream>

class graph {

  public:

    /*
     * The constructor creates the graph by initializing the hashTable of vertices.
     * By default, a capcity of 100 is assumed.
     */
    graph(int capacity=100);

    /*
     * Insert a vertex into the graph with string 'id'
     *
     * Returns true on success, false if the vertex exists already.
     */
    bool insertVertex(std::string id);

    /*
     * Check if a vertex with string 'id' exists in the graph
     *
     * Returns true if it exists, false if it does not exist.
     */
    bool checkVertex(std::string id);

    /*
     * Insert an edge with given start and end string ids with cost dist
     */
    void insertEdge(std::string start, std::string end, int dist);

    /*
     * Dijkstra's algorithm.
     * Finds the least-cost path from vertex 'sourceVertex' to each other vertex.
     */
    void runDijkstra(std::string sourceVertex);

    /*
     * Write the output file to filename specified in string 'filename'
     * based on instructor specficiations.
     * Vertices are listed in the order in which they were stored with
     * each listing the least-cost path from the source vertex to it.
     */
    void writeOut(std::string filename);

  private:
    // Nested edge class
    class edge;

    // Nested vertex class
    class vertex {
      public:
        std::string name;
        bool isKnown;
        int dist;
        std::list<edge *> adj;
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
