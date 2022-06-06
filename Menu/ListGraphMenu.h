//
// Created by Luka Mitrovic on 20/05/2022.
//

#ifndef SDIZO2_LISTGRAPHMENU_H
#define SDIZO2_LISTGRAPHMENU_H

#include "../Graph/ListGraph.h"

class ListGraphMenu {
public:
    void listGraphCreationMode();
    void listGraphOperationMode();
private:
    ListGraph *graphToOperateWith;
};

#endif //SDIZO2_LISTGRAPHMENU_H
