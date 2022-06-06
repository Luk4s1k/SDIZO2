//
// Created by Luka Mitrovic on 28/05/2022.
//

#include "ListGMeasurments.h"
#define PRIM_FILE "/Users/lukamitrovic/Desktop/ListGraph/prim.txt"
#define KRUSKAL_FILE "/Users/lukamitrovic/Desktop/ListGraph/KRUSKAL.txt"
#define DIJKSTRA_FILE "/Users/lukamitrovic/Desktop/ListGraph/DIJKSTRA.txt"
#define FORD_FILE "/Users/lukamitrovic/Desktop/ListGraph/FORD.txt"

void ListGMeasurments::measurePrim(float density, int vertexes, int measurmentsAmount) {
    std::ofstream myfile;
    long averagetime = 0;
    testGraph = new ListGraph();
    myfile.open (PRIM_FILE,std::fstream::app);
    testGraph->createRandomGraph(vertexes, false,vertexDensity(density,vertexes));
    for(int i = 0; i < measurmentsAmount; i++){
        time.measureStart();
        testGraph->prim();
        time.measureEnd();
        averagetime += time.getTime();
    }
    myfile << "Prim " << density << " % " << vertexes << " measurments : " << averagetime/measurmentsAmount/pow(10,6) << std::endl;
    std::cout<<averagetime/measurmentsAmount/pow(10,6)<<std::endl;
    myfile.close();
    delete testGraph;
}

void ListGMeasurments::measureKruskal(float density, int vertexes, int measurmentsAmount) {
    std::ofstream myfile;
    long averagetime = 0;
    testGraph = new ListGraph();
    myfile.open (KRUSKAL_FILE,std::fstream::app);
    testGraph->createRandomGraph(vertexes, false,vertexDensity(density,vertexes));
    for(int i = 0; i < measurmentsAmount; i++){
//        time.measureStart();
//        time.measureEnd();
//        averagetime += testGraph->kruskal();
    }
    myfile << "Kruskal " << density << " % " << vertexes << " measurments : " << averagetime/measurmentsAmount/pow(10,6) << std::endl;
    std::cout<< averagetime/measurmentsAmount/pow(10,6)<<std::endl;
    myfile.close();
    delete testGraph;
}

void ListGMeasurments::measureDijkstra(float density, int vertexes, int measurmentsAmount) {
    std::cout << "entering function " << density << std::endl;
    std::ofstream myfile;
    long averagetime = 0;
    testGraph = new ListGraph();
    myfile.open (DIJKSTRA_FILE,std::fstream::app);
    testGraph->createRandomGraph(vertexes, true,vertexDensity(density,vertexes));
    for(int i = 0; i < measurmentsAmount; i++){
        time.measureStart();
        testGraph->dijkstra(0);
        time.measureEnd();
        averagetime += time.getTime();
    }
    myfile << "Dijkstra " << density << " % " << vertexes << " measurments : " << averagetime/measurmentsAmount/pow(10,6) << std::endl;
    std::cout<<averagetime/measurmentsAmount/pow(10,6)<<std::endl;
    myfile.close();
    delete testGraph;
}

void ListGMeasurments::measureBellmanFord(float density, int vertexes, int measurmentsAmount) {
    std::ofstream myfile;
    long averagetime = 0;
    testGraph = new ListGraph();
    myfile.open (FORD_FILE,std::fstream::app);
    testGraph->createRandomGraph(vertexes, true,vertexDensity(density,vertexes));
    for(int i = 0; i < measurmentsAmount; i++){
        time.measureStart();
        testGraph->bellmanFord(0);
        time.measureEnd();
        averagetime += time.getTime();
    }
    myfile << "Ford " << density << " % " << vertexes << " measurments : " << averagetime/measurmentsAmount/pow(10,6) << std::endl;
    std::cout<<averagetime/measurmentsAmount/pow(10,6)<<std::endl;
    myfile.close();
    delete testGraph;
}

void ListGMeasurments::executeAllTests() {
    executePrimTests();
    executeKruskalTests();
    executeDijkstraTests();
    executeFordTests();
}

int ListGMeasurments::vertexDensity(float density, int vertexes) {
    return ((vertexes*(vertexes-1))/2)*density;
}

void ListGMeasurments::executePrimTests() {
    std::cout << "------- PRIM MEASURMENTS ------ " << std::endl;
    std::cout << "Measuring 100 vertexes" << std::endl;
    measurePrim(0.25,100,10);
    measurePrim(0.5,100,10);
    measurePrim(0.75,100,10);
    measurePrim(0.99,100,10);
    std::cout << "Measuring 500 vertexes" << std::endl;
    measurePrim(0.25,500,1);
    measurePrim(0.5,500,1);
    measurePrim(0.75,500,1);
    measurePrim(0.99,500,1);
    std::cout << "Measuring 700 vertexes" << std::endl;
    measurePrim(0.25,700,10);
    measurePrim(0.5,700,10);
    measurePrim(0.75,700,10);
    measurePrim(0.99,700,10);
    std::cout << "Measuring 1000 vertexes" << std::endl;
    measurePrim(0.25,1000,10);
    measurePrim(0.5,1000,10);
    measurePrim(0.75,1000,10);
    measurePrim(0.99,1000,10);
    std::cout << "Measuring 1500 vertexes" << std::endl;
    measurePrim(0.25,1500,10);
    measurePrim(0.5,1500,10);
    measurePrim(0.75,1500,10);
    measurePrim(0.99,1500,10);
}

void ListGMeasurments::executeKruskalTests() {
    std::cout << "------- KRUSKAL MEASURMENTS ------ " << std::endl;
    std::cout << "Measuring 100 vertexes" << std::endl;
    measureKruskal(0.25,100,10);
    measureKruskal(0.5,100,10);
    measureKruskal(0.75,100,10);
    measureKruskal(0.99,100,10);
    std::cout << "Measuring 500 vertexes" << std::endl;
    measureKruskal(0.25,500,10);
    measureKruskal(0.5,500,10);
    measureKruskal(0.75,500,10);
    measureKruskal(0.99,500,10);
    std::cout << "Measuring 700 vertexes" << std::endl;
    measureKruskal(0.25,700,10);
    measureKruskal(0.5,700,10);
    measureKruskal(0.75,700,10);
    measureKruskal(0.99,700,10);
    std::cout << "Measuring 1000 vertexes" << std::endl;
    measureKruskal(0.25,1000,10);
    measureKruskal(0.5,1000,10);
    measureKruskal(0.75,1000,10);
    measureKruskal(0.99,1000,10);
    std::cout << "Measuring 1500 vertexes" << std::endl;
    measureKruskal(0.25,1500,10);
    measureKruskal(0.5,1500,10);
    measureKruskal(0.75,1500,10);
    measureKruskal(0.99,1500,10);
}

void ListGMeasurments::executeDijkstraTests() {
    std::cout << "------- DIJKSTRA MEASURMENTS ------ " << std::endl;
    std::cout << "Measuring 100 vertexes" << std::endl;
    measureDijkstra(0.25,100,10);
    measureDijkstra(0.5,100,10);
    measureDijkstra(0.75,100,10);
    measureDijkstra(0.99,100,10);
    std::cout << "Measuring 500 vertexes" << std::endl;

    measureDijkstra(0.25,500,10);
    measureDijkstra(0.5,500,10);
    measureDijkstra(0.75,500,10);
    measureDijkstra(0.99,500,10);
    std::cout << "Measuring 700 vertexes" << std::endl;

    measureDijkstra(0.25,700,10);
    measureDijkstra(0.5,700,10);
    measureDijkstra(0.75,700,10);
    measureDijkstra(0.99,700,10);
    std::cout << "Measuring 1000 vertexes" << std::endl;

    measureDijkstra(0.25,1000,10);
    measureDijkstra(0.5,1000,10);
    measureDijkstra(0.75,1000,10);
    measureDijkstra(0.99,1000,10);
    std::cout << "Measuring 1500 vertexes" << std::endl;

    measureDijkstra(0.25,1500,10);
    measureDijkstra(0.5,1500,10);
    measureDijkstra(0.75,1500,10);
    measureDijkstra(0.99,1500,10);
}

void ListGMeasurments::executeFordTests() {
    std::cout << "------- BELLMAN-FORD MEASURMENTS ------ " << std::endl;
    std::cout << "Measuring 100 vertexes" << std::endl;
    measureBellmanFord(0.25,100,10);
    measureBellmanFord(0.5,100,10);
    measureBellmanFord(0.75,100,10);
    measureBellmanFord(0.99,100,10);
    std::cout << "Measuring 500 vertexes" << std::endl;

    measureBellmanFord(0.25,500,10);
    measureBellmanFord(0.5,500,10);
    measureBellmanFord(0.75,500,10);
    measureBellmanFord(0.99,500,10);
    std::cout << "Measuring 700 vertexes" << std::endl;

    measureBellmanFord(0.25,700,10);
    measureBellmanFord(0.5,700,10);
    measureBellmanFord(0.75,700,10);
    measureBellmanFord(0.99,700,10);
    std::cout << "Measuring 1000 vertexes" << std::endl;

    measureBellmanFord(0.25,1000,10);
    measureBellmanFord(0.5,1000,10);
    measureBellmanFord(0.75,1000,10);
    measureBellmanFord(0.99,1000,10);
    std::cout << "Measuring 1500 vertexes" << std::endl;

    measureBellmanFord(0.25,1500,10);
    measureBellmanFord(0.5,1500,10);
    measureBellmanFord(0.75,1500,10);
    measureBellmanFord(0.99,1500,10);
}
