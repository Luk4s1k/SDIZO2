//
// Created by Luka Mitrovic on 20/05/2022.
//

#include "BinaryHeap.h"

BinaryHeap::BinaryHeap(){}
BinaryHeap::~BinaryHeap()
{
    sizeVar = 0;
    free(heap);
    heap = NULL;
}

void BinaryHeap::showBinaryHeap() {
    int levels = log2(sizeVar)+1;
    int i = 0;
    int j = 1;
    while(i < sizeVar) {
        while((i < j) && (i < sizeVar)) {
            for(int i = 0;i<levels*2;i++)
                cout<<" ";
            cout << heap[i] << " ";
            for(int i = 0;i<levels;i++)
                cout<<" ";
            i++;
        }
        levels = levels/2;
        cout << endl;
        j = j * 2 + 1;
    }
}

void BinaryHeap::readFromFile(string filename) {
    int temporaryInt = 0, temporarySize = 0;
    ifstream in(filename);
    if(in.is_open()) {
        in>>temporarySize;
        for(int i=0;i<temporarySize;i++) {
            in>>temporaryInt;
            addItem(temporaryInt);
        }
        in.close();
    }
}

void BinaryHeap::addItem(int item) {
    int* tmp = (int*)calloc((sizeVar+1),sizeof(int));
    for(int i=0;i<sizeVar;i++) {
        tmp[i]= heap[i];
    }
    free(heap);
    heap = tmp;
    addToNormalizedPosition(item);
}

int BinaryHeap::deleteVertex() {
    int deletedValue = heap[0];
    if(sizeVar == 0) return - 1;
    heap[0] = heap[sizeVar - 1];
    heap = (int*)realloc(heap, sizeof(int)*(sizeVar - 1));
    sizeVar--;
    normalize(0);
    return deletedValue;
}

void BinaryHeap::normalize(int index) {
    int temp;
    int leftItem = 2*index + 1;
    int rightItem = 2*index + 2;

    if(rightItem<sizeVar) {
        if(heap[rightItem]<heap[leftItem] && heap[rightItem]<heap[index]) {
            temp = heap[index];
            heap[index] = heap[rightItem];
            heap[rightItem] = temp;
            normalize(rightItem);
        }
        else {
            if(heap[leftItem]<heap[index]) {
                temp = heap[index];
                heap[index] = heap[leftItem];
                heap[leftItem] = temp;
                normalize(leftItem);
            }
        }
    }
    else
    if(leftItem<sizeVar) {
        if(heap[leftItem]<heap[index]) {
            temp = heap[index];
            heap[index] = heap[leftItem];
            heap[leftItem] = temp;
            normalize(leftItem);
        }
    }
    else return;
}

void BinaryHeap::initializate(int sizeValue, int value) {
    heap = (int*)calloc(sizeValue,sizeof(int));
    for(int i=0;i<sizeValue;i++) {
        addToNormalizedPosition(value);
    }
}

bool BinaryHeap::findElement(int i,int item) {
    if(item<heap[i]) return false;
    if(item==heap[i]) {
        return true;
    }

    int left = 2*i + 1;
    if(left >= sizeVar)
        return false;

    bool findLeft = findElement(left, item);
    if(findLeft!=false) {
        return true;
    }

    int right = 2*i + 2;
    if(right >= sizeVar)
        return false;
    else
        return findElement(right,item);

}

void BinaryHeap::addToNormalizedPosition(int element) {
    int parentNode;
    int i = sizeVar;
    heap[sizeVar] = element;
    parentNode = (i - 1)/2;
    while(i > 0) {
        if(heap[i]<heap[parentNode]) {
            int tmp = heap[i];
            heap[i] = heap[parentNode];
            heap[parentNode] = tmp;
        }
        i = parentNode;
        parentNode = (i - 1)/2;
    }
    sizeVar++;
}

void BinaryHeap::deleteHeap() {
    while(sizeVar != 0) {
        deleteVertex();
    }
}