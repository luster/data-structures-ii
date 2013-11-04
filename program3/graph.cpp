// Ethan Lusterman
// ECE165, Fall 2013
// graph.cpp

#include "graph.h"
using namespace std;

#define INFINITY INT_MAX

graph::graph(int capacity) {

    this->vertex_map = new hashTable(capacity);

}


bool graph::insertVertex(std::string id) {

    if (this->checkVertex(id))
        return false;

    vertex *v = new vertex();
    v->name = id;

    this->vertex_map->insert(id, v);
    this->vertices.push_back(v);
    return true;

}


bool graph::checkVertex(std::string id) {

    if (this->vertex_map->contains(id))
        return true;
    else
        return false;

}


void graph::insertEdge(std::string start, std::string end, int dist) {

    this->insertVertex(start);
    this->insertVertex(end);

    bool keyExists = false;
    vertex *dest = static_cast<vertex *> (this->vertex_map->getPointer(end, &keyExists));

    edge *e = new edge();
    e->cost = dist;
    e->destination = dest;

    vertex *source = static_cast<vertex *> (this->vertex_map->getPointer(start, &keyExists));
    source->adj.push_back(e);

    return;

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
        list<edge *>::iterator it2;
        if (v->dist == INFINITY)
            continue;

        for (it2=v->adj.begin(); it2!=v->adj.end(); it2++) {
            int newCost = v->dist + (*it2)->cost;
            if (newCost < (*it2)->destination->dist) {
                (*it2)->destination->dist = newCost;
                Q.setKey((*it2)->destination->name,newCost);
                (*it2)->destination->prev = v;
            }
        }
    }

    return;

}


void graph::writeOut(std::string filename) {

    ofstream out(filename.c_str());

    list<vertex *>::iterator it;
    string path;

    for (it=this->vertices.begin(); it!=this->vertices.end(); it++) {
        out << (*it)->name << ": ";
        vertex *v = (*it);

        if (v->dist == INFINITY)
            out << "NO PATH" << endl;
        else if (v->dist == 0)
            out << v->dist << " [" << v->name << "]" << endl;
        else {
            out << v->dist << " [";
            path = v->name;
            while (v->prev != NULL) {
                path = v->prev->name + ", " + path;
                v = v->prev;
            }
            out << path << "]" << endl;
        }
    }

    return;

}
