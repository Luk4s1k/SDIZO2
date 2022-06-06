//
// Created by Luka Mitrovic on 20/05/2022.
//

#include "MatrixGraphMenu.h"
#include <iostream>

void MatrixGraphMenu::matrixGraphCreationMode() {
    int MatrixGraphCreationOption;
    int isDirectedOption = 0;
    std::cout << " ------- Matrix Graph ---------- " << std::endl;
    std::cout << " 1 - Create custom graph"<< std::endl;
    std::cout << " 2 - Create graph from file"<< std::endl;
    std::cin >> MatrixGraphCreationOption;
    if(MatrixGraphCreationOption == 1){
        graphToOperateWith = new MatrixGraph();
        std::cout << "Is graph directed ? Y-1 / N-2" << std::endl;
        std::cin >> isDirectedOption;
        if(isDirectedOption == 1){
            graphToOperateWith->setDirected(true);
        }else if (isDirectedOption == 2 ) {
            graphToOperateWith->setDirected(false);
        }else {
            std::cout << "Invalid option " << std::endl;
            matrixGraphCreationMode();
        }
        matrixGraphOperationMode();
    }else if (MatrixGraphCreationOption == 2){
        std::string filename;
        std::cout << "FILE PATH:";
        std::cin >> filename;
        graphToOperateWith= new MatrixGraph(filename);
        graphToOperateWith->print();
        std::cout << "Is graph directed ? Y-1 / N-2" << std::endl;
        std::cin >> isDirectedOption;
        if(isDirectedOption == 1){
            graphToOperateWith->setDirected(true);
        }else if (isDirectedOption == 2 ) {
            graphToOperateWith->setDirected(false);
        }else {
            std::cout << "Invalid option " << std::endl;
            matrixGraphCreationMode();
        }
        matrixGraphOperationMode();
    }else {
        std::cout << "INVALID OPTION !!!" << std::endl;
        matrixGraphOperationMode();
    }
}

void MatrixGraphMenu::matrixGraphOperationMode() {
    int listGraphOperationOption;
    int value = 0, index = 0;
    int positionFound = 0;
    int isDirected = graphToOperateWith->isDirected();
    std::cout << " ------- Graph ---------- " << std::endl;
    std::cout << " 1 - Prim's algorithm"<< std::endl;
    std::cout << " 2 - Kruskal's algorithm"<< std::endl;
    std::cout << " 3 - Dijkstra's algorithm"<< std::endl;
    std::cout << " 4 - Bellman-Ford's algorithm"<< std::endl;
    std::cout << " 5 - Print graph"<< std::endl;
    std::cout << " 6 - EXIT "<< std::endl;
    std::cin >> listGraphOperationOption;
    switch(listGraphOperationOption){
        default:
            std::cout << "INVALID CHOICE" << std::endl;
            matrixGraphOperationMode();
        case 6:
            return;
        case 1:
            if(isDirected) cout << "Graph cannot be Directed" << endl;
            else
                graphToOperateWith->prim();
            matrixGraphOperationMode();
            break;
        case 2:
            if(isDirected) cout << "Graph cannot be Directed" << endl;
            else
                graphToOperateWith->kruskal();
            matrixGraphOperationMode();
            break;
        case 3:
            if(!isDirected) cout << "Graph must be Directed" << endl;
            else
                graphToOperateWith->dijkstra(0);
            matrixGraphOperationMode();
            break;
        case 4:
            if(!isDirected) cout << "Graph must be Directed" << endl;
            else
                graphToOperateWith->bellmanFord(0);
            matrixGraphOperationMode();
            break;
        case 5:
                graphToOperateWith->print();
            matrixGraphOperationMode();
            break;

    }
}
