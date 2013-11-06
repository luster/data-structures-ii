// Ethan Lusterman
// ECE165, Fall 2013
// dijkstra.cpp

#include <iostream>
#include "graph.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>

using namespace std;

/*
 * Each line of the input filestream 'in' is of the form
 *      startNodeName endNodeName costValue
 *
 * This function reads and inserts edges and nodes into the
 * graph 'myGraph' from the input filestream.
 */
void loadGraph(graph &myGraph, ifstream &in) {

    string line, start, end;
    int cost;

    while (getline(in,line)) {
        istringstream stream(line);
        stream >> start >> end >> cost;

        myGraph.insertEdge(start,end,cost);
    }
    return;

}

/*
 * This function prompts the user for a valid graph file
 * and starting vertex, then runs Dijkstra's algorithm
 * to determine the least-cost path (if one exists) from
 * the starting vertex to every other vertex in the graph.
 * The time to run the algorithm is displayed, and then
 * the least-cost paths are written to a user specified
 * output file.
 */
int main() {

    string infile, outfile;
    string vertexStart;
    bool inputGood = false;

    cout << "Enter name of graph file: ";
    cin >> infile;
    ifstream input(infile.c_str());
    if (!input.is_open()) {
        cout << "Invalid Filename: " << infile << endl;
        exit(1);
    }

    graph myGraph(100);
    loadGraph(myGraph, input);

    while (!inputGood) {
        cout << "Enter a valid vertex id for the starting vertex: ";
        cin >> vertexStart;

        if (myGraph.checkVertex(vertexStart))
            inputGood = true;
        else
            cout << "Invalid Vertex: " << vertexStart << endl;
    }

    clock_t t1 = clock();
    myGraph.runDijkstra(vertexStart);
    clock_t t2 = clock();

    double timeDijk = ((double) (t2-t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: ";
    cout << timeDijk << endl;

    cout << "Enter name of output file: ";
    cin >> outfile;

    myGraph.writeOut(outfile);

    input.close();

    return 0;
}
