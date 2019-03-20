//
// Created by sohayla on 20/03/19.
//

#ifndef JAVA_COMPILER_EDGE_H
#define JAVA_COMPILER_EDGE_H

#include <string>
#include "Node.h"

using namespace std;
class Edge {
private:
    Node* source;
    Node* Destination;
    string weight;

public:
    Edge(Node* src, Node* dst, string weight);
    Node* getSource();
    Node* getDestination();
    string getWeight();

};


#endif //JAVA_COMPILER_EDGE_H
