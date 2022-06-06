//
// Created by Luka Mitrovic on 20/05/2022.
//

#include "ListGraph.h"
#include "../Measurments/MeasureTime.h"

ListGraph::~ListGraph() {
    clear();
}
// Default constructor
ListGraph::ListGraph() {
    this->head = nullptr;
    this->nodes = 0;
    this->edges = 0;
    this->directed = false;
    this->edgeMatrix = new int*[edges];
}

/*
 * Creates @param nodes number of nodes
 * and sets the directed parameter of graph
 * */
ListGraph::ListGraph(int nodes, bool isDirected) : nodes(nodes), directed(isDirected) {
    this->edges = 0;
    this->head = new node*[nodes];
    for(int i=0;i<this->nodes;i++) {
        head[i] = nullptr;
    }
}
// Getter for directed attribute
bool ListGraph::isDirected() {
    return this->directed;
}
// Setter for directed attribute
void ListGraph::setDirected(bool isDirected) {
    this->directed = isDirected;
}
// Getter for directed attribute
int ListGraph::getEdges() {
    return this->edges;
}
// Getter for nodes attribute
int ListGraph::getNodes() {
    return this->nodes;
}
// Getter for head attribute
node** ListGraph::getHead() {
    return head;
}

// Function created to be able to call destructor when needed not to
// delete the object but only content
void ListGraph::clear() {
    for (int i = 0; i < this->nodes; i++) {
        delete this->head[i];
        this->head[i] = nullptr;
    }
    delete[] this->head;

    for(int i=0;i<this->nodes ;i++)
        delete[] this->edgeMatrix[i];
    delete[] this->edgeMatrix;

    this->head = nullptr;
    this->nodes = 0;
    this->edges = 0;
}

ListGraph::ListGraph(string filename) {
    ifstream file(filename);
    if(file.is_open()) {
        int edgeNum, nodeNum;
        file>>edgeNum;
        file>>nodeNum;

        string str;
        getline(file, str);

        this->edgeMatrix = new int*[edgeNum];

        this->nodes = nodeNum;
        this->head = new node*[nodes];
        for(int i = 0;i < this->nodes ;i++) {
            head[i] = nullptr;
        }

        int start, finish, weight;
        for(int i=0;i<edgeNum;i++) {
            file>>start;
            file>>finish;
            file>>weight;
            connect(start,finish, weight);
            this->edgeMatrix[i] = new int[2];
            this->edgeMatrix[i][0] = start;
            this->edgeMatrix[i][1] = finish;
        }
    }
}

bool ListGraph::connect(int start, int finish, int weight) {
    if(start < 0 || finish < 0 || start >= nodes || finish >= nodes) {
        return false;
    }

    // Creating new node
    node* newNode = new node;
    newNode->value = finish;
    newNode->weight = weight;
    newNode->next = nullptr;

    node* currentNode = head[start];
    node* prevNode = currentNode;

    // If strart has no neighbours set him as first */
    if(head[start] == nullptr) {
        head[start] = newNode;
    }
    else    // if has neighbours put him in the end
    {
        while(currentNode!=nullptr) {
            // Insert in sorted order
            if(currentNode->value > newNode->value) {
                if(prevNode == currentNode) {
                    head[start] = newNode;      // if bigger insert new node
                    newNode->next = currentNode;    // move current as next
                }
                else {
                    prevNode->next = newNode;
                    newNode->next = currentNode;
                }
                break;
            }
            else
            if(currentNode->value == newNode->value) {
                this->edges++;
                return true;
            }
            // move to another neighbour
            prevNode = currentNode;
            currentNode = currentNode->next;
        }

        if(currentNode == nullptr)
            prevNode->next = newNode;
    }
    if(!this->directed)
        return connect(finish,start,weight);


    this->edges++;
    return true;
}

bool ListGraph::disconnect(int start, int finish) {
    if(start<0 || finish<0 || start>=nodes || finish>=nodes) return false;

    node* currentNode = head[start];
    node* prevNode = currentNode;

    if(head[start] == nullptr) {
        return true;
    }
    else {
        while(currentNode!=nullptr) {
            if(currentNode->value > finish) {
                this->edges--;
                return true;
            }
            else if(currentNode->value == finish) {
                if(currentNode->next!=nullptr) {
                    if(prevNode!= currentNode) {
                        prevNode->next = currentNode->next;
                    }
                    else {
                        head[start] = currentNode->next;
                    }
                } else {
                    if(prevNode->next != nullptr) {
                        prevNode->next = nullptr;
                    }
                    else {
                        head[start] = nullptr;
                    }
                }
                currentNode = nullptr;
                delete currentNode;
                break;
            }

            prevNode = currentNode;
            currentNode = currentNode->next;
        }
    }
    if(!this->directed)
        return disconnect(finish,start);

    return true;
}

void ListGraph::print() {
    if(head == nullptr) {
        cout<<" Empty "<<endl;
    }
    for(int i = 0;i < nodes; i++) {
        cout << i;
        node* currentNode = head[i];
        cout<<": ";
        while(currentNode != nullptr) {
            cout<<currentNode->value<<"["<<currentNode->weight<<"]"<<" => "; /*Print edge of neighbour with weight */
            currentNode = currentNode->next;
        }
        cout<<"null"<<endl;
    }
}

void ListGraph::dijkstra(int start) {
    BinaryHeap bheap;
    int u = 0;  /*edge which we are checking  */

    int* edge = new int[2];
    bool* validated = new bool[this->nodes]; /*neighbout edges */
    int* d = new int[this->nodes];  /*distances*/
    int* p = new int[this->nodes];  /*end edges*/
    int* neighbours = nullptr;

    /* Start initialization */
    for(int i=0;i<this->nodes;i++) {
        d[i] = INT_MAX;
        p[i] = INT_MAX;
        validated[i] = false;
    }
    d[start] = 0;

    /* Check for negative weights */
    for(int i=0;i<this->edges;i++) {
        edge = this->edgeMatrix[i];
        if(getWeight(edge[i],edge[i])<0) {
            cout<<"Dijkstra algorythm doesnt work with negative weights"<<endl;
            return;
        }
    }

    for(int i=0;i<this->nodes;i++)
        bheap.addItem(d[i]);

    while(bheap.sizeVar!=0) {
        int x = bheap.deleteVertex(); /*get minimal weight*/

        for(int i = 0;i < this->nodes;i++) {
            if(d[i] == x && validated[i] == false)
                u = i;
        }

        neighbours = countNeighbours(u);

        for(int i = 0; i < this->neighbours;i++) { /*check route to every edge  */
            int v = neighbours[i];
            if (d[v] > d[u] + getWeight(u,v)) {
                d[v] = d[u] + getWeight(u,v); /* relaxation */
                p[v] = u;
            }
        }
        /*Mark as visited */
        validated[u] = true;
        bheap.deleteHeap();

        /*create queue based on corrected routes */
        for(int i=0;i<this->nodes;i++) {
            if(validated[i]!=true)
                bheap.addItem(d[i]);
        }
    }

    /* print via stack */
    stack<int> roads;
    cout << "Start = "<< start << endl;

    for(int i = 1;i < this->nodes;i++) {
        cout<<"To: "<<i<<" Dist: "<<d[i]<<" Path: ";
        int address = i;
        roads.push(i);

        if(p[address]!=INT_MAX) {
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
    delete[] validated;
    delete[] p;
    delete[] d;
    delete[] neighbours;
}

int* ListGraph::countNeighbours(int index) {
    int neigboursCount = 0;
    node* start = head[index];
    /*count number off neighbours */
    while(start!=nullptr) {
        neigboursCount++;
        start = start->next;
    }

      this->neighbours  = neigboursCount;


    int* neigbourArray = new int[neigboursCount];
    start = head[index];
    for(int i=0;i<neigboursCount;i++) {
        neigbourArray[i] = start->value;
        start = start->next;
    }
    return neigbourArray;
}

int ListGraph::getWeight(int start, int finish) {
    node* startNode = head[start];
    while(startNode!=nullptr) {
        if(startNode->value==finish)
            return startNode->weight;
        startNode = startNode->next;
    }
    return 0;
}

void ListGraph::bellmanFord(int start) {
    int counter = 0, relaxationCounter = 0;
    int* edge = new int[2];
    int* d = new int[this->nodes];  // array of distances
    int* p = new int[this->nodes];  // koncowe wieszcholki
    for(int i = 0;i < this->nodes;i++) {
        d[i] = INT_MAX-100;
        p[i] = INT_MAX;
    }
    d[start] = 0;
    for(int i=0;i < this->nodes - 1;i++) {
        for(int j = 0;j < getEdges();j++) {
            edge = this->edgeMatrix[counter];
            if(d[edge[1]] > d[edge[0]] + getWeight(edge[0],edge[1])) {
                d[edge[1]] = d[edge[0]] + getWeight(edge[0],edge[1]);
                p[edge[1]] = edge[0];
                relaxationCounter++;
            }
            counter++;
        }
        counter = 0; // we need to move again through all vertexes
        if(relaxationCounter==0) break; // no relaxation -> finish
        else relaxationCounter = 0;
    }
    for(int i = 0; i < this->edges; i++) {
        edge = this->edgeMatrix[i];
        if(d[edge[1]] > d[edge[0]] + getWeight(edge[0],edge[1])) {
            cout<<"Negative cykle detected"<<endl;
            return;
        }
    }
    // Print results
    stack<int> roads;
    cout << "Start = " << start << endl;
    for(int i = 1;i < this->nodes;i++) {
        cout<<"To: "<<i<<" Dist: "<<d[i]<<" Path: ";
        int address = i;
        roads.push(i);
        // Put this on stack
        while(p[address]!=INT_MAX) {
            roads.push(p[address]);
            address = p[address];
        }
        // Get from stack and print
        while(!roads.empty()) {
            if(roads.size()==1)
                cout<<roads.top()<<"";
            else
                cout<<roads.top()<<"->";
            roads.pop();
        }
        cout<<endl;
    }
    delete edge;
    delete[] d;
    delete[] p;
}

void ListGraph::prim() {
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

    // set up the priority queue
    for(int i = 0;i < this->nodes;i++)
        bHeap.addItem(key[i]);

    while(bHeap.sizeVar != 0) {
        int u = 0;
        int x = bHeap.deleteVertex();
        // Searching for the edge with least value
        for(int i=0;i<this->nodes;i++) {
            if(key[i] == x && validated[i] == false)
                u = i;
        }

        neighbours = countNeighbours(u);
        for(int i = 0; i < this->neighbours ;i++) { // Checkc route to everyone
            int v = neighbours[i];
            if(bHeap.sizeVar!=0 && bHeap.findElement(0,key[v]) && getWeight(u,v) < key[v]) {
                if(validated[v] == true) continue;
                key[v] = getWeight(u,v);
                p[v] = u;
            }
        }

        validated[u] = true;
        bHeap.deleteHeap();

        for(int i = 0;i < this->nodes;i++) {
            if(validated[i]!=true)
                bHeap.addItem(key[i]);
        }
    }

    int sum = 0;
    for(int i=1;i<this->nodes;i++) {
        cout<<"("<<p[i]<<";"<<i<<")"<<" -> "<<key[i]<<endl;
        sum+=key[i];
    }
    cout<<"MST = "<<sum<<endl;
    delete[] validated;
    delete[] neighbours;
    delete[] key;
    delete[] p;
}

void ListGraph::kruskal() {// temp
//    MeasureTime firtstime;// temp
//    MeasureTime secondtime;// temp
//    int timeMeasurment = 0;// temp
//    firtstime.measureStart();// temp
    bool* isEdgeMakeSolution = new bool[this->edges];
    for(int i = 0;i < this->edges;i++) {
        isEdgeMakeSolution[i] = false;
    }
    int* grupa = new int[this->nodes];
    listEdge* actualEdge = nullptr;
//    firtstime.measureEnd();// temp
//    timeMeasurment += firtstime.getTime(); // temp

    listEdge** edges = createSortedEdgesList();
//    secondtime.measureStart();// temp
    // Creating subtrees
    for(int i=0;i<this->nodes;i++) {
        grupa[i] = i;
    }
    for(int i = 0;i<this->edges;i++) {
        actualEdge = edges[i];
        if(grupa[actualEdge->start] != grupa[actualEdge->finish]) {
            isEdgeMakeSolution[i] = true;
            int changeValue = grupa[actualEdge->finish];
            for(int i = 0;i < this->nodes;i++) {
                if(grupa[i] == changeValue)
                    grupa[i] = grupa[actualEdge->start];
            }
        }
    }
//    secondtime.measureEnd();// temp
//    timeMeasurment+=secondtime.getTime();// temp
    // Print result
    int sum = 0;
    for(int i=0;i<this->edges;i++) {
        if(isEdgeMakeSolution[i]) {
            cout<<"("<<edges[i]->start<<";"<<edges[i]->finish<<")"<<" -> "<<edges[i]->weight<<endl;
            sum+=edges[i]->weight;
        }
    }
    cout<<"MST = "<<sum<<endl;
    delete[] isEdgeMakeSolution;
    delete[] grupa;
    delete[] edges;
    delete actualEdge;
//    return timeMeasurment;// temp

}

listEdge** ListGraph::createSortedEdgesList() {
    listEdge** unsortedEdges = new listEdge*[getEdges()];

    // create simple list of vertexes with weights
    for(int i=0;i<this->edges;i++) {
        unsortedEdges[i] = new listEdge;
        unsortedEdges[i]->start = this->edgeMatrix[i][0];
        unsortedEdges[i]->finish = this->edgeMatrix[i][1];
        unsortedEdges[i]->weight = getWeight(this->edgeMatrix[i][0],this->edgeMatrix[i][1]);
    }

    // Sort by weights
    listEdge* temp = nullptr;
    int SIZE = this->getEdges();
    for(int i = 0;i < SIZE-1;i++) {
        listEdge* maximum = unsortedEdges[0];
        int indmax = 0;
        for(int j = 0;j < SIZE - i;j++) {
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

void ListGraph::createRandomGraph(int vertexNumber, bool direction, int edgeNumber) {
    clear();
    /* Check max number of vertexes*/
    if(edgeNumber>(vertexNumber)*(vertexNumber-1)*0.5 || edgeNumber<vertexNumber-1 && !direction) {
        cout<<"Invalid vertex number"<<endl;
        return;
    }

    this->nodes = vertexNumber;
    this->directed = direction;
    this->edges = 0;

    this->edgeMatrix = new int*[edgeNumber];

    this->head = new node*[vertexNumber];
    for(int i=0;i < this->nodes;i++) {
        head[i] = nullptr;
    }

    int maxEdgeNumber = (vertexNumber * vertexNumber - vertexNumber) / 2; /* graf pelny */
    int edgeCounter = 0;

    /* Tworzenie grafu minimalnego = spojnego */
    for (int i = 0; i < this->nodes-1;i++) { /* minimalna ilosc krawedzi = n - 1 aby graf byl spojny */
        connect(i,i + 1,rand()%(1000));
         /*tworzymy miejsce na jedna krawedz */
        this->edgeMatrix[edgeCounter] = new int[2];
        this->edgeMatrix[edgeCounter][0] = i;
        this->edgeMatrix[edgeCounter][1] = i+1;
        edgeCounter++;
    }
    int i,j;
    /*Nastepnie tworzymy aby osiagnac zadana ilosc krawedzi */
    while(this->edges!=edgeNumber) {
        for(int i=0;i<vertexNumber;i++) {
            for(int j=0;j<vertexNumber;j++) {
                if(this->edges==edgeNumber) return;
                if(getWeight(i,j)==0 && i!=j) {    /*jezeli nie ma polaczenia oraz wierzcholek nie wskazuje na siebie*/
                    connect(i,j,rand()%(INT_MAX-200));   /*polacz*/
                    this->edgeMatrix[edgeCounter] = new int[2]; /*tworzymy miejsce na jedna krawedz */
                    this->edgeMatrix[edgeCounter][0] = i;
                    this->edgeMatrix[edgeCounter][1] = j;
                    edgeCounter++;
                }
            }
        }
    }
}
