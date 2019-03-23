//
// Created by sohayla on 20/03/19.
//

#ifndef JAVA_COMPILER_GRAPH_H
#define JAVA_COMPILER_GRAPH_H

#include <vector>
#include <string>
#include "Node.h"
#include "Edge.h"

using namespace std;

class Graph {
private:
    Node* start;
    Node* end; // for purpose of merging only
    vector<Node*> states;
    vector<Edge*> transitions;
public:
    Graph();
    bool addEdge(Node * source, Node* Destination, Definition* weight);
    void mergeGraph(vector<Edge*> edges, vector<Node*> states);
    //bool mergeGraph(Graph* graph, string operation);
    Node* getStartState();
    Node* getEndState();
    vector<Node*> getAllstates();
    void setStart(Node* new_s);
    void setEnd(Node* new_e);

    vector<Node*> getAcceptanceStates();
    Edge* getTransition(Node* src, Node* dst);
    vector<Edge*> getEdges();
    Node* getTargetNode(Node* src, Definition* weight);

};


#endif //JAVA_COMPILER_GRAPH_H
