//
// Created by sohayla on 20/03/19.
//

#ifndef JAVA_COMPILER_NODE_H
#define JAVA_COMPILER_NODE_H


#include "Edge.h"
#include <vector>
using namespace std;

class Node {
private:
    int id;
    vector<Edge*> inwardEdges;
    vector<Edge*> outwardEdges;
    bool accepted;
public:
    Node(int id);
    vector<Edge*> getInwardEdges();
    vector<Edge*> getOutwardEdges();
    bool insertEdge(Edge* edge, bool in);
    bool getStatus();
    bool setStatus(bool accepted);


};


#endif //JAVA_COMPILER_NODE_H
