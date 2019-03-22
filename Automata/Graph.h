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
    Node* end;
    vector<Node*> states;
    vector<Edge*> transitions;
    string id;
public:
    Graph(string id);
    string getId();
    bool addEdge(Node * source, Node* Destination, Definition* weight_regex);
    //bool mergeGraph(Graph* graph, string operation);
    Node* getStartState();
    Node* getEndState();
    vector<Node*> getAllstates();
    vector<Node*> getAcceptanceStates();
    Edge* getTransition(Node* src, Node* dst);
    vector<Edge*> edges();
    Node* getTargetNode(Node* src, Definition* weight);

};


#endif //JAVA_COMPILER_GRAPH_H
