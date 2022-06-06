//
// Created by Luka Mitrovic on 20/05/2022.
//

#include "ListGraphMenu.h"
#include <iostream>

void ListGraphMenu::listGraphCreationMode() {
    int ListGraphCreationOption;
    int isDirectedOption = 0;
    std::cout << " ------- Listed Graph ---------- " << std::endl;
    std::cout << " 1 - Create custom graph"<< std::endl;
    std::cout << " 2 - Create graph from file"<< std::endl;
    std::cin >> ListGraphCreationOption;
    if(ListGraphCreationOption == 1){
        graphToOperateWith= new ListGraph();
        std::cout << "Is graph directed ? Y-1 / N-2" << std::endl;
        std::cin >> isDirectedOption;
        if(isDirectedOption == 1){
            graphToOperateWith->setDirected(true);
        }else if (isDirectedOption == 2 ) {
            graphToOperateWith->setDirected(false);
        }else {
            std::cout << "Invalid option " << std::endl;
            listGraphCreationMode();
        }
        listGraphOperationMode();
    }else if (ListGraphCreationOption == 2){
        std::string filename;
        std::cout << "FILE PATH:";
        std::cin >> filename;
        graphToOperateWith= new ListGraph(filename);
        graphToOperateWith->print();
        std::cout << "Is graph directed ? Y-1 / N-2" << std::endl;
        std::cin >> isDirectedOption;
        if(isDirectedOption == 1){
            graphToOperateWith->setDirected(true);
        }else if (isDirectedOption == 2 ) {
            graphToOperateWith->setDirected(false);
        }else {
            std::cout << "Invalid option " << std::endl;
            listGraphCreationMode();
        }
        listGraphOperationMode();
    }else {
        std::cout << "INVALID OPTION !!!" << std::endl;
        listGraphOperationMode();
    }
}

void ListGraphMenu::listGraphOperationMode() {
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
            listGraphOperationMode();
        case 6:
            return;
        case 1:
            if(isDirected) cout << "Graph cannot be Directed" << endl;
            else
                graphToOperateWith->prim();
            listGraphOperationMode();
            break;
        case 2:
            if(isDirected) cout << "Graph cannot be Directed" << endl;
            else
                graphToOperateWith->kruskal();
            listGraphOperationMode();
            break;
        case 3:
            if(!isDirected) cout << "Graph must be Directed" << endl;
            else
                graphToOperateWith->dijkstra(0);
            listGraphOperationMode();
            break;
        case 4:
            if(!isDirected) cout << "Graph must be Directed" << endl;
            else
                graphToOperateWith->bellmanFord(0);
            listGraphOperationMode();
            break;
        case 5:
                graphToOperateWith->print();
            listGraphOperationMode();
            break;

    }
}
