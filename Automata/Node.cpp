//
// Created by sohayla on 20/03/19.
//

#include <algorithm>
#include "Node.h"

Node::Node(int id) {
    this->id = id;
    this->status = N_ACC;
}

vector<Edge*> Node::getInwardEdges() {
    return this->inwardEdges;
}

vector<Edge*> Node::getOutwardEdges() {
    return this->outwardEdges;
}

string Node::getStatus() {
    return this->status;
}

void Node::setStatus(string st) {
    this->status = st;
}

bool Node::insertEdge(Edge *edge, bool in) {
    if(in) {
        if(find(inwardEdges.begin(), inwardEdges.end(), edge) != inwardEdges.end())
            return false;
        inwardEdges.push_back(edge);
    } else {
        if(find(outwardEdges.begin(), outwardEdges.end(), edge) != outwardEdges.end())
            return false;
        outwardEdges.push_back(edge);
    }
    return true;
}