//
// Created by Luka Mitrovic on 20/05/2022.
//

#ifndef SDIZO2_LISTGMEASURMENTS_H
#define SDIZO2_LISTGMEASURMENTS_H
#include "MeasureTime.h"
#include "../Graph/ListGraph.h"

class ListGMeasurments {
public:
    ListGraph *testGraph;
    MeasureTime time;

    void measurePrim(float density, int vertexes, int measurmentsAmount);
    void measureKruskal(float density, int vertexes, int measurmentsAmount);
    void measureDijkstra(float density, int vertexes, int measurmentsAmount);
    void measureBellmanFord(float density, int vertexes, int measurmentsAmount);

    int vertexDensity(float density, int vertexes);

    void executeAllTests();
    void executePrimTests();
    void executeKruskalTests();
    void executeDijkstraTests();
    void executeFordTests();
};

#endif //SDIZO2_LISTGMEASURMENTS_H
