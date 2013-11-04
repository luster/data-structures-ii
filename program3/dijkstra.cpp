#include <iostream>
#include "graph.h"
#include <fstream>
#include <sstream>
#include <ctime>
#include <string>

using namespace std;

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

int main() {
    // a few declarations, the graph to be stored, filenames and streams
    string infile, outfile;
    string vertexStart;
    bool inputGood = false;

    // user enters name of file specifying graph
    cout << "Enter name of graph file: ";
    cin >> infile;
    ifstream input(infile.c_str());
    if (!input.is_open()) {
        cout << "Invalid Filename: " << infile << endl;
        exit(1);
    }

    // load graph
    graph myGraph(100);
    loadGraph(myGraph, input);

    // user enters the id of a starting vertex until it's a valid vertex
    while (!inputGood) {
        cout << "Enter a valid vertex id for the starting vertex: ";
        cin >> vertexStart;

        if (myGraph.checkVertex(vertexStart))
            inputGood = true;
        else
            cout << "Invalid Vertex: " << vertexStart << endl;
    }

    // time Dijkstra
    clock_t t1 = clock();
    myGraph.runDijkstra(vertexStart);
    clock_t t2 = clock();

    double timeDijk = ((double) (t2-t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: ";
    cout << timeDijk << endl;

    // prompt user for output file
    cout << "Enter name of output file: ";
    cin >> outfile;

    // write output file
    myGraph.writeOut(outfile);

    input.close();

    return 0;
}
