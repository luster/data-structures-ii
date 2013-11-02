// Ethan Lusterman
// ECE165, Fall 2013
// graph.cpp

#include "graph.h"
#include <climits>
#include <fstream>
using namespace std;

#define INFINITY INT_MAX

graph::graph(int capacity) {
    vertex_map = new hashTable(capacity);
}

bool graph::insertVertex(std::string id) {
    if (checkVertex(id))
        return false;

    vertex *v = new vertex();
    v->name = id;
    //v->isKnown = false;
    //v->dist = INFINITY;
    //v->prev = NULL;

    this->vertex_map->insert(id, v);
    this->vertices.push_back(v);
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
    heap Q(this->vertices.size()+1);

    list<vertex *>::iterator it;
    for (it=this->vertices.begin(); it!=this->vertices.end(); it++) {
        if ((*it)->name == sourceVertex)
            (*it)->dist = 0;
        else
            (*it)->dist = INFINITY;
        (*it)->isKnown = false;
        (*it)->prev = NULL;
        Q.insert((*it)->name, (*it)->dist, (*it));
    }

    vertex *v;
    while (Q.deleteMin(NULL,NULL,&v) != 1) {
        v->isKnown = true;
        list<edge *>::iterator it;

        for (it=v->adj.begin(); it!=v->adj.end(); it++) {
            int newCost = v->dist + (*it)->cost;
            if (newCost < (*it)->destination->dist) {
                Q.setKey((*it)->destination->name,newCost);
                (*it)->destination->prev = v;
            }
        }
    }


    return;
}


void graph::writeOut(std::string filename) {
    ofstream out(filename.c_str());

    list<vertex *>::iterator it;

    for (it=this->vertices.begin(); it!=this->vertices.end(); it++) {
        out << (*it)->name << ": ";
        vertex *v = (*it);
        if (!v->prev) {
            if (!v->dist)
                out << "[" << v->name << "]" << endl;
            else
                out << " NO PATH" << endl;
        }
        else {
            out << "[";
            while (v->prev != NULL) {
                if (v->prev && v->prev->prev)
                    out << v->name << ", ";
                else
                    out << v->name << "]" << endl;
                v = v->prev;
            }
        }
    }

    return;
}