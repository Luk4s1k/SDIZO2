//
// Created by Luka Mitrovic on 28/05/2022.
//

#include "MatrixGMeasurments.h"
#define PRIM_FILE "/Users/lukamitrovic/Desktop/MatrixGraph/prim.txt"
#define KRUSKAL_FILE "/Users/lukamitrovic/Desktop/MatrixGraph/KRUSKAL.txt"
#define DIJKSTRA_FILE "/Users/lukamitrovic/Desktop/MatrixGraph/DIJKSTRA.txt"
#define FORD_FILE "/Users/lukamitrovic/Desktop/MatrixGraph/FORD.txt"

void MatrixGMeasurments::measurePrim(float density, int vertexes, int measurmentsAmount) {
    std::ofstream myfile;
    long averagetime = 0;
    testGraph = new MatrixGraph(vertexes,false);
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

void MatrixGMeasurments::measureKruskal(float density, int vertexes, int measurmentsAmount) {
    std::ofstream myfile;
    long averagetime = 0;
    testGraph = new MatrixGraph(vertexes,false);
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

void MatrixGMeasurments::measureDijkstra(float density, int vertexes, int measurmentsAmount) {
    std::cout << "entering function " << density << std::endl;
    std::ofstream myfile;
    long averagetime = 0;
    testGraph = new MatrixGraph();
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

void MatrixGMeasurments::measureBellmanFord(float density, int vertexes, int measurmentsAmount) {
    std::ofstream myfile;
    long averagetime = 0;
    testGraph = new MatrixGraph();
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

void MatrixGMeasurments::executeAllTests() {
    executePrimTests();
    executeKruskalTests();
    executeDijkstraTests();
    executeFordTests();
}

int MatrixGMeasurments::vertexDensity(float density, int vertexes) {
    return ((vertexes*(vertexes-1))/2)*density;
}

void MatrixGMeasurments::executePrimTests() {
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

void MatrixGMeasurments::executeKruskalTests() {
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

void MatrixGMeasurments::executeDijkstraTests() {
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

void MatrixGMeasurments::executeFordTests() {
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
