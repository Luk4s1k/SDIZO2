//
// Created by Luka Mitrovic on 20/05/2022.
//

#ifndef SDIZO2_MATRIXGRAPHMENU_H
#define SDIZO2_MATRIXGRAPHMENU_H

#include "../Graph/MatrixGraph.h"

class MatrixGraphMenu {
public:
    void matrixGraphCreationMode();
    void matrixGraphOperationMode();
private:
    MatrixGraph *graphToOperateWith;
};


#endif //SDIZO2_MATRIXGRAPHMENU_H
