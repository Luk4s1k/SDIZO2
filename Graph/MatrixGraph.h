//
// Created by Luka Mitrovic on 20/05/2022.
//

#ifndef SDIZO2_MATRIXGRAPH_H
#define SDIZO2_MATRIXGRAPH_H


#include <iostream>
#include <fstream>
#include <stack>
#include "ListGraph.h"
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct edge {
    int start;
    int finish;
    int weight;
};

class MatrixGraph
{
public:
    MatrixGraph();
    MatrixGraph(int vertex, bool isDirected);
    virtual ~MatrixGraph();
    MatrixGraph(string filename);

    void print();

    bool connect(int startVertex, int endVertex, int edge);
    bool disconnect(int startVertex, int endVertex);

    int getEdgeNumber();
    int getNodeNumber();

    void dijkstra(int start);
    void bellmanFord(int start);
    void prim();
    void kruskal();

    void createRandomGraph(int vertexNumber,bool direction, int edgeNumber);

    edge** createSortedEdgesList();

    int getWeight(int start, int finish);

    void clear(int n, bool isDirected);
    int** getMatrix();

    int* countNeighbours(int start);

    bool isDirected();
    void setDirected(bool isDirected);
private:
    bool directed;
    int** matrix;
    int** edgeMatrix;
    int edges;
    int nodes;
    int neighbours = 0;
};

#endif //SDIZO2_MATRIXGRAPH_H
