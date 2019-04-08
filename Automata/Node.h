//
// Created by sohayla on 20/03/19.
//

#ifndef JAVA_COMPILER_NODE_H
#define JAVA_COMPILER_NODE_H


#include "Edge.h"
#include <vector>
using namespace std;
#define N_ACC "n"
class Node {
private:
    int id;
    vector<Edge*> inwardEdges;
    vector<Edge*> outwardEdges;
    string status;
    int priority;
public:
    Node(int id);
    vector<Edge*> getInwardEdges();
    vector<Edge*> getOutwardEdges();
    bool insertEdge(Edge* edge, bool in);
    string getStatus();
    void setStatus(string st);
    int getId();
    void setPriority(int p);
    int getPriority();

};


#endif //JAVA_COMPILER_NODE_H
