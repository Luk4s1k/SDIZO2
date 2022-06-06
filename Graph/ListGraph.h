//
// Created by Luka Mitrovic on 20/05/2022.
//

#ifndef SDIZO2_LISTGRAPH_H
#define SDIZO2_LISTGRAPH_H

#include <iostream>
#include <fstream>
#include "../BinaryHeap/BinaryHeap.h"
#include <stack>
#include "MatrixGraph.h"

using namespace std;

struct listEdge {
    int start;
    int finish;
    int weight;
};

struct node {
    int value;
    int weight;
    node* next;
};

class ListGraph
{
    node **head;
    bool directed;
    int nodes;
    int edges;
    int neighbours;
    int** edgeMatrix;

public:
    ListGraph();
    ListGraph(int vertexNumber, bool isDirected);
    ListGraph(string filename);

    void createRandomGraph(int vertexes,bool directed, int edges);
    listEdge** createSortedEdgesList();

    bool isDirected();
    void setDirected(bool isDirected);

    int getNodes();
    int getEdges();
    node** getHead();
    int getWeight(int start, int finish);
    int* countNeighbours(int index);

    bool connect(int startVertex, int endVertex, int weight);
    bool disconnect(int startVertex, int endVertex);

    void dijkstra(int start);
    void bellmanFord(int start);
    void prim();
    void kruskal();

    void clear();
    void print();
    virtual ~ListGraph();
};

#endif //SDIZO2_LISTGRAPH_H
