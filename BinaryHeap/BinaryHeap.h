//
// Created by Luka Mitrovic on 20/05/2022.
//

#ifndef SDIZO2_BINARYHEAP_H
#define SDIZO2_BINARYHEAP_H
#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
using namespace std;

class BinaryHeap
{
public:
    int sizeVar = 0;
    int* heap = NULL;

    BinaryHeap();
    virtual ~BinaryHeap();

    void readFromFile(string filename);
    void showBinaryHeap();
    void addItem(int item);
    int deleteVertex();
    void normalize(int index);
    void initializate(int sizeValue, int elem);
    bool findElement(int i,int item);
    void deleteHeap();
    void addToNormalizedPosition(int element);
};


#endif //SDIZO2_BINARYHEAP_H
