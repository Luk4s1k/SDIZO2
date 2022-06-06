//
// Created by Luka Mitrovic on 20/05/2022.
//

#include "MatrixGraph.h"
#include "../BinaryHeap/BinaryHeap.h"
#include "../Measurments/MeasureTime.h"
MatrixGraph::MatrixGraph() {
    this->nodes = 0;
    this->directed = false;
}

MatrixGraph::~MatrixGraph() {
    clear(0, false);
}

MatrixGraph::MatrixGraph(int vertexNumber, bool isDirected) : nodes(vertexNumber), directed(isDirected) {
    this->edges = 0;
    if(vertexNumber < 0) {
        this->nodes = 0;
    }
    else {
        this->nodes = vertexNumber;
    }

    /*Tworzenie poczatkowej matrixy sasiedztwa */
    this->matrix = new int*[vertexNumber];
    for(int i=0;i<vertexNumber; i++) {
        this->matrix[i] = new int[vertexNumber];
        for(int j=0;j<vertexNumber;j++) {
            this->matrix[i][j] = 0;
        }
    }
}

int* MatrixGraph::countNeighbours(int index) {
    int neighbours = 0;
    /* Obliczamy ilosc sasiadow */
    for(int j = 0;j<nodes;j++) {
        if(this->matrix[index][j]!=0)
            neighbours++;
    }
    /*Ustwaiamy ile ma sasiadow*/
    this->neighbours = neighbours;

    /* Tworzymy liste indeksow sasiadow */
    int* neighbourArray = new int[neighbours];
    int counter = 0;
    for(int j = 0;j<nodes;j++) {
        if(this->matrix[index][j]!=0) {
            neighbourArray[counter] = j;
            counter++;
        }
    }
    return neighbourArray;
}

int MatrixGraph::getWeight(int start, int finish) {
    return this->matrix[start][finish];
}

bool MatrixGraph::connect(int startVertex, int endVertex, int edge) {
    if(startVertex<0 || endVertex<0 || startVertex>nodes || endVertex>nodes) return false;

    this->edges++; /* Inkrementacja liczby krawedzi */
    this->matrix[startVertex][endVertex] = edge; /* Wpisywanie wartosci krawedzi do matrixy sasiedztwa */

    if(!this->directed) /* Jezeli graf nie jest skierowany wtedy od koncowego do poczatkowego taka sama krawedz */
        this->matrix[endVertex][startVertex] = edge;
    return true;
}

bool MatrixGraph::disconnect(int startVertex, int endVertex) {
    if(startVertex<0 || endVertex<0 || startVertex>nodes || endVertex>nodes) return false;

    /* Usuwanie krawedzi poprzez wpisanie 0 */
    if(matrix[startVertex][endVertex]!=0)
        this->edges--;
    this->matrix[startVertex][endVertex] = 0;

    /* Jezeli graf nie jest skierowany istnieje taka sama krawedz z wierzcholka koncowego */
    if(!this->directed)
        this->matrix[endVertex][startVertex] = 0;
    return true;
}

void MatrixGraph::print() { /*Wypisanie matrixy sasiadztwa */
    for(int i=0;i<nodes;i++) {
        for(int j = 0;j<nodes;j++)
            cout<<this->matrix[i][j]<<" ";
        cout<<endl;
    }
}

int MatrixGraph::getNodeNumber() {
    return nodes;
}

int** MatrixGraph::getMatrix() {
    return matrix;
}

int MatrixGraph::getEdgeNumber() {
    return edges;
}

bool MatrixGraph::isDirected() {
    return directed;
}

void MatrixGraph::setDirected(bool tmpDirected) {
    this->directed = tmpDirected;
}

void MatrixGraph::clear(int nodeNumber, bool isDirected) {
    /*Usuniecie poprzedniego*/
    for(int i=0;i<this->nodes ;i++)
        delete[] this->matrix[i];
    delete[] this->matrix;

    for(int i=0;i<this->nodes ;i++)
        delete[] this->edgeMatrix[i];
    delete[] this->edgeMatrix;

    /* Inicjalizacja nowego */
    this->nodes = nodeNumber;
    this->edges = 0;
    this->directed = isDirected;
    this->matrix = new int*[this->nodes];

    for(int i=0;i<nodeNumber;i++) {
        this->matrix[i] = new int[nodeNumber];
        for(int j=0;j<nodeNumber;j++)
            this->matrix[i][j] = 0;
    }
}

MatrixGraph::MatrixGraph(string filename) {
    ifstream file(filename);
    if(file.is_open()) {
        int edgeNum, nodeNum;
        file>>edgeNum;
        file>>nodeNum;

        string str;
        getline(file, str);
        clear(nodeNum,this->directed);

        this->edgeMatrix = new int*[edgeNum]; /*tworzenie listy krawedzi potrzebnej do algroytmow */

        int start, finish, weight;
        for(int i=0;i<edgeNum;i++) {
            file>>start;
            file>>finish;
            file>>weight;
            connect(start,finish, weight);
            this->edgeMatrix[i] = new int[2]; /*tworzymy miejsce na jedna krawedz */
            this->edgeMatrix[i][0] = start;
            this->edgeMatrix[i][1] = finish;
        }

    }
}

void MatrixGraph::dijkstra(int start) {
    BinaryHeap bheap; /*kolejka*/
    int u = 0;  /*aktualnie sprawdzany wierzcholek */

    int* edge = new int[2];
    bool* validated = new bool[this->nodes]; /*tablica sprawdzonych wierzcholkow*/
    int* d = new int[this->nodes];  /*tablica aktualnych odleglosci*/
    int* p = new int[this->nodes];  /*tablica koncowych wierzcholkow*/
    int* neighbours = nullptr; /* zbior sasiadow wierzcholka */

    /* Poczatkowa inicjalizacja */
    for(int i=0;i<this->nodes;i++) {
        d[i] = INT_MAX;
        p[i] = INT_MAX;
        validated[i] = false;
    }
    d[start] = 0;

    /*Inicjalizacja kolejki priorytetowej (kopiec-min) */
    for(int i=0;i<this->nodes;i++)
        bheap.addItem(d[i]);

    /* Sprawdzenie wag ujemnych */
    for(int i=0;i<this->edges;i++) {
        edge = this->edgeMatrix[i];
        if(getWeight(edge[0],edge[1])<0) {
            cout<<"Istnieja wagi ujemne, algorytm Dijkstry nie moze byc wykonany"<<endl;
            return;
        }
    }

    while(bheap.sizeVar!=0) {
        int u;
        int x = bheap.deleteVertex(); /*Pobieramy najmniejsza wage*/
        /*Znalezenie numeru wierzcholka o najmniejszej wadze d[i]*/
        for(int i=0;i<this->nodes;i++) {
            if(d[i] == x && validated[i] == false)
                u = i;
        }
        /*szukamy liste indeksow sasiadow */
        neighbours = countNeighbours(u);
        for(int i = 0; i<this->neighbours;i++) { /*Sprwadzamy droge do kazdego */
            int v = neighbours[i];
            if (d[v] > d[u] + getWeight(u,v)) {
                d[v] = d[u] + getWeight(u,v); /* Relaksacja */
                p[v] = u;
            }
        }
        /*Oznaczamy wierzcholek jako sprawdzony */
        validated[u] = true;
        bheap.deleteHeap();

        /*Tworzymy kolejke na podstawie korektowanych drog */
        for(int i=0;i<this->nodes;i++) {
            if(validated[i]!=true)
                bheap.addItem(d[i]);
        }
    }

    /** Wyswietlenie wyniku z wykorzystaniem stosu **/
    stack<int> roads;
    cout << "Start = "<< start << endl;
    for(int i = 1;i<this->nodes;i++) {
        cout <<"To: "<< i <<" Dist: "<< d[i] <<" Path: ";
        int address = i;
        roads.push(i);
        while(p[address]!=INT_MAX) {
            roads.push(p[address]);
            address = p[address];
        }
        while(!roads.empty()) {
            if(roads.size()==1)
                cout<<roads.top()<<"";
            else
                cout<<roads.top()<<"->";
            roads.pop();
        }
        cout<<endl;
    }
    /* Zwolnienie pamieci */
    delete[] validated;
    delete[] p;
    delete[] d;
    delete[] neighbours;
    delete edge;
}

void MatrixGraph::bellmanFord(int start) {
    int relaxationCounter = 0;
    int counter = 0;
    int* edge = new int[2];
    int* d = new int[this->nodes];  /*tablica aktualnych odleglosci*/
    int* p = new int[this->nodes];  /*tablica koncowych wierzcholkow*/
    for(int i=0;i<this->nodes;i++) {
        d[i] = INT_MAX-100;
        p[i] = INT_MAX;
    }
    d[start] = 0;

    for(int i=0;i<this->nodes-1;i++) {
        for(int j=0;j<getEdgeNumber();j++) {
            edge = this->edgeMatrix[counter];
            if(d[edge[1]] > d[edge[0]] + getWeight(edge[0],edge[1])) {
                d[edge[1]] = d[edge[0]] + getWeight(edge[0],edge[1]);
                relaxationCounter++;
                if(edge[1]==0) continue;
                p[edge[1]] = edge[0];
            }
            counter++;
        }
        counter = 0; /*bo trzeba znow przejsc przez kazda krawedz*/
        if(relaxationCounter==0) break; /*jezeli nie bylo zadnej relaksacji -> konczymy algroytm */
        else relaxationCounter = 0;
    }
    for(int i=0;i<this->edges;i++) {
        edge = this->edgeMatrix[i];
        if(d[edge[1]] > d[edge[0]] + getWeight(edge[0],edge[1])) {
            cout<<"Cykl ujemny w algorytmie Bellmana-Forda"<<endl;
            return;
        }
    }

    /*Wyswietlanie wyniku*/
    stack<int> roads;
    cout<<"Start = "<<start<<endl;
    for(int i = 1;i<this->nodes;i++) {
        cout<<"To: "<<i<<" Dist: "<<d[i]<<" Path: ";
        int address = i;
        roads.push(i);
        while(p[address]!=INT_MAX) {
            roads.push(p[address]);
            address = p[address];
        }
        while(!roads.empty()) {
            if(roads.size()==1)
                cout<<roads.top()<<"";
            else
                cout<<roads.top()<<"->";
            roads.pop();
        }
        cout<<endl;
    }
    /*Zwolnienie pamieci */
    delete edge;
    delete[] d;
    delete[] p;
}

void MatrixGraph::prim() {
    bool* validated  = new bool[this->nodes];
    int* neighbours = nullptr;
    int* key = new int[this->nodes];
    int* p = new int[this->nodes];
    BinaryHeap bHeap;

    for(int i=0;i<this->nodes;i++) {
        key[i] = INT_MAX;
        validated[i] = false;
    }
    key[0] = 0;
    p[0] = INT_MAX;

    /*Inicjalizacja kolejki priorytetowej*/
    for(int i=0;i<this->nodes;i++)
        bHeap.addItem(key[i]);

    while(bHeap.sizeVar!=0) {
        int u = 0;
        int x = bHeap.deleteVertex();
        /*Znalezenie numeru wierzcholka o najmniejszej wadze d[i]*/
        for(int i=0;i<this->nodes;i++) {
            if(key[i] == x && validated[i] == false)
                u = i;
        }

        neighbours = countNeighbours(u);

        for(int i = 0; i<this->neighbours;i++) { /*Sprawdzamy droge do kazdego */
            int v = neighbours[i];
            if(bHeap.sizeVar!=0 && bHeap.findElement(0,key[v]) && getWeight(u,v) < key[v]) {
                if(validated[v]==true) continue;
                key[v] = getWeight(u,v);
                p[v] = u;
            }
        }

        validated[u] = true;
        bHeap.deleteHeap();

        for(int i=0;i<this->nodes;i++) {
            if(validated[i]!=true)
                bHeap.addItem(key[i]);
        }
    }

    /*Koncowe wyswietlanie*/
    int sum = 0;
    for(int i=1;i<this->nodes;i++) {
        cout<<"("<<p[i]<<";"<<i<<")"<<" -> "<<key[i]<<endl;
        sum+=key[i];
    }
    cout<<"MST = "<<sum<<endl;

    /*Zwolnienie pamieci */
    delete[] validated;
    delete[] neighbours;
    delete[] key;
    delete[] p;
}

void MatrixGraph::kruskal() {
//    MeasureTime firtstime;// temp
//    MeasureTime secondtime;// temp
//    int timeMeasurment = 0;// temp
//    firtstime.measureStart();// temp
    bool* isEdgeMakeSolution = new bool[this->edges];
    for(int i=0;i<this->edges;i++) {
        isEdgeMakeSolution[i] = false;
    }
    int* grupa = new int[this->nodes];
    edge* actualEdge = nullptr;
//    firtstime.measureEnd();// temp
//    timeMeasurment += firtstime.getTime(); // temp
    edge** edges = createSortedEdgesList();
//    secondtime.measureStart();// temp
    /* Tworzenie poddrzew */
    for(int i=0;i<this->nodes;i++) {
        grupa[i] = i;
    }
    for(int i = 0;i<this->edges;i++) {
        actualEdge = edges[i];
        if(grupa[actualEdge->start] != grupa[actualEdge->finish]) {
            isEdgeMakeSolution[i] = true;
            int changeValue = grupa[actualEdge->finish]; /* kopia indeksu grupy do zmiany zeby nie byla utracona po pierwszej podmianie */
            for(int i=0;i<this->nodes;i++) {
                if(grupa[i] == changeValue)
                    grupa[i] = grupa[actualEdge->start];
            }
        }
    }
//    secondtime.measureEnd();// temp
//    timeMeasurment+=secondtime.getTime();// temp
    /*Wyswietlenie wyniku*/
    int sum = 0;
    for(int i=0;i<this->edges;i++) {
        if(isEdgeMakeSolution[i]) {
            cout<<"("<<edges[i]->start<<";"<<edges[i]->finish<<")"<<" -> "<<edges[i]->weight<<endl;
            sum+=edges[i]->weight;
        }
    }
    cout<<"MST = "<<sum<<endl;
    /*Zwolnienie pamieci*/
    delete[] isEdgeMakeSolution;
    delete[] grupa;
    delete[] edges;
    delete actualEdge;
//    return timeMeasurment;
}

edge** MatrixGraph::createSortedEdgesList() {
    edge** unsortedEdges = new edge*[getEdgeNumber()];
    /*Tworzenie nieposortowanej listy krawedzi wraz z wagami*/
    for(int i=0;i<this->edges;i++) {
        unsortedEdges[i] = new edge;
        unsortedEdges[i]->start = this->edgeMatrix[i][0];
        unsortedEdges[i]->finish = this->edgeMatrix[i][1];
        unsortedEdges[i]->weight = this->matrix[this->edgeMatrix[i][0]][this->edgeMatrix[i][1]];
    }

    /* Sortowanie selekcyjne wedlug wag */
    edge* temp = nullptr;
    int SIZE = this->getEdgeNumber();
    for(int i=0;i<SIZE-1;i++) {
        edge* maximum = unsortedEdges[0];
        int indmax = 0;
        for(int j=0;j<SIZE-i;j++) {
            if(unsortedEdges[j]->weight>maximum->weight) {
                maximum=unsortedEdges[j];
                indmax = j;
            }
        }
        temp = unsortedEdges[SIZE-1-i];
        unsortedEdges[SIZE-1-i] = maximum;
        unsortedEdges[indmax] = temp;
    }
    return unsortedEdges;
}

void MatrixGraph::createRandomGraph(int vertexNumber, bool isDirected, int edgeNumber) {
    /* Usuniecie poprzedniego gdy istnial i inicjowanie nowego */
//    clear(vertexNumber,isDirected);

    /*Tworzenie listy krawedzi dla alg. Kruskala */
    this->edgeMatrix = new int*[edgeNumber];

    /* Maks. ilosc krawedzi to graf pelny wynosi n*(n-1)/2 a minimalna to n-1*/
    if(edgeNumber>(vertexNumber)*(vertexNumber-1)*0.5 || edgeNumber<vertexNumber-1 && !isDirected) {
        cout<<"Nie moze byc tyle krawedzi!"<<endl;
        return;
    }

    int maxEdgeNumber = (vertexNumber * vertexNumber - vertexNumber) / 2; /* graf pelny */
    int edgeCounter = 0;

    /* Tworzenie grafu minimalnego = spojnego */
    for (int i=0; i<this->nodes-1;i++) { /* minimalna ilosc krawedzi = n - 1 aby graf byl spojny */
        connect(i,i + 1,rand()%(INT_MAX-200));
        this->edgeMatrix[edgeCounter] = new int[2]; /*tworzymy miejsce na jedna krawedz */
        this->edgeMatrix[edgeCounter][0] = i;
        this->edgeMatrix[edgeCounter][1] = i+1;
        edgeCounter++;
    }

    int i= 0,j = 0;
    /*Nastepnie tworzymy aby osiagnac zadana ilosc krawedzi */
    while(this->edges!=edgeNumber) {
        i = rand()%vertexNumber;
        j = rand()%vertexNumber;
        if(this->matrix[i][j]==0 && i!=j) {    /*jezeli nie ma polaczenia oraz wierzcholek nie wskazuje na siebie*/
            connect(i,j,rand()%(1000));   /*polacz*/
            this->edgeMatrix[edgeCounter] = new int[2]; /*tworzymy miejsce na jedna krawedz */
            this->edgeMatrix[edgeCounter][0] = i;
            this->edgeMatrix[edgeCounter][1] = j;
            edgeCounter++;
        }
    }
}