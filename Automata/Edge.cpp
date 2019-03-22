//
// Created by sohayla on 20/03/19.
//

#include "Edge.h"
#include "Definition.h"

Edge::Edge(Node *src, Node *dst, Definition *weight) {
    this->source = src;
    this->destination = dst;
    this->weight = weight;
}

Node* Edge::getDestination() {
    return this->destination;
}

Node* Edge::getSource() {
    return this->source;
}

Definition* Edge::getWeight() {
    return this->weight;
}
