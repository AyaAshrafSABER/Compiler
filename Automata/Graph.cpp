//
// Created by sohayla on 20/03/19.
//

#include <algorithm>
#include "Graph.h"
Graph::Graph() {
    start = NULL;
    end = NULL;
    states.clear();
    transitions.clear();
}

bool Graph::addEdge(Node *source, Node *Destination, Definition *weight) {
    if(find(states.begin(), states.end(), source) == states.end())
        states.push_back(source);
    if(find(states.begin(), states.end(),Destination ) == states.end())
        states.push_back(Destination);
    if(this->getTargetNode(source, weight) == Destination)
        return false;
    Edge* transition = new Edge(source, Destination, weight);
    this->transitions.push_back(transition);
    return true;

}

Node* Graph::getTargetNode(Node *src, Definition *weight) {
    if(find(states.begin(), states.end(), src) == states.end())
        return NULL;
    vector<Edge*> outward = src->getOutwardEdges();
    for(int i = 0; i < outward.size(); i++) {
        if(outward[i]->getWeight() == weight) {
            return outward[i]->getDestination();
        }
    }
    return NULL;

}

vector<Node*> Graph::getAcceptanceStates() {
    vector<Node*> acc;
    for(int i = 0; i < states.size(); i++) {
        if(states[i]->getStatus() != N_ACC) {
            acc.push_back(states[i]);
        }
    }
    return acc;
}

vector<Node*> Graph::getAllstates() {
    return this->states;
}

Node* Graph::getEndState() {
    return this->end;
}
Node* Graph::getStartState() {
    return this->start;
}

Edge* Graph::getTransition(Node *src, Node *dst) {
    if(find(states.begin(), states.end(), src) == states.end())
        return NULL;
    if(find(states.begin(), states.end(), dst) == states.end())
        return NULL;
    vector<Edge*> outward = src->getOutwardEdges();
    for(int i = 0; i < outward.size(); i++) {
        if(outward[i]->getDestination() == dst) {
            return outward[i];
        }
    }
    return NULL;
}

vector<Edge*> Graph::getEdges() {
    return this->transitions;
}