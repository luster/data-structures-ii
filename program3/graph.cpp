// Ethan Lusterman
// ECE165, Fall 2013
// graph.cpp

#include "graph.h"
#include <climits>
using namespace std;

graph::graph(int capacity) {
    vertex_map = new hashTable(capacity);
}

bool graph::insertVertex(std::string id) {
    if (checkVertex(id))
        return false;

    vertex *v = new vertex();
    v->name = id;
    v->isKnown = false;
    v->dist = INT_MAX;
    v->prev = NULL;

    vertex_map->insert(id, v);
    vertices.push_back(v);
    return true;
}


bool graph::checkVertex(std::string id) {
    if (vertex_map->contains(id))
        return true;
    else
        return false;
}


bool graph::insertEdge(std::string start, std::string end, int dist) {

    insertVertex(start);
    insertVertex(end);

    bool keyExists = false;
    vertex *dest = static_cast<vertex *> (vertex_map->getPointer(end, &keyExists));
    edge *e = new edge();
    e->cost = dist;
    e->destination = dest;

    vertex *source = static_cast<vertex *> (vertex_map->getPointer(start, &keyExists));
    source->adj.push_back(e);

    return true;
}


void graph::runDijkstra(std::string sourceVertex) {
    return;
}


void graph::writeOut(std::string filename) {
    return;
}
