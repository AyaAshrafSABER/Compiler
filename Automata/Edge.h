//
// Created by sohayla on 20/03/19.
//

#ifndef JAVA_COMPILER_EDGE_H
#define JAVA_COMPILER_EDGE_H

#include <string>

using namespace std;
class Node;
class Definition;
class Edge {
private:
    Node* source;
    Node* destination;
    Definition *weight;

public:
    Edge(Node* src, Node* dst, Definition* weight);
    Node* getSource();
    Node* getDestination();
    Definition* getWeight();

};


#endif //JAVA_COMPILER_EDGE_H
